#include "CameraUtils/CamerasManager.hpp"
#include "CameraUtils/CullingMaskUtils.hpp"
#include "CameraUtils/EnumUtils.hpp"

using namespace std;
using namespace UnityEngine;

namespace CameraUtils {
    //region Cameras

    map<Camera *, CameraFlags> CamerasManager::Cameras = map<Camera *, CameraFlags>();

    void CamerasManager::RegisterDesktopCamera(Camera *camera, CameraFlags cameraFlags) {
        cameraFlags |= CameraFlags::CF_Desktop;
        RegisterCamera(camera, cameraFlags);
        CullingMaskUtils::SetupDesktopCamera(camera);
    }

    void CamerasManager::RegisterHMDCamera(Camera *camera, CameraFlags cameraFlags) {
        cameraFlags |= CameraFlags::CF_HMD;
        RegisterCamera(camera, cameraFlags);
        CullingMaskUtils::SetupHMDCamera(camera);
    }

    void CamerasManager::RegisterMirrorCamera(Camera *mirrorCamera, Camera *currentCamera) {
        auto cameraFlags = CameraFlags::CF_Mirror;

        if (Cameras.contains(currentCamera)) {
            auto rc = Cameras[currentCamera];
            cameraFlags |= rc;
        }

        RegisterCamera(mirrorCamera, cameraFlags);
        CullingMaskUtils::SetupMirrorCamera(mirrorCamera, currentCamera);
    }

    void CamerasManager::RegisterCamera(Camera *camera, CameraFlags cameraFlags) {
        UnRegisterCamera(camera);
        Cameras[camera] = cameraFlags;
        AddAllEffectsToCamera({camera, cameraFlags});
    }

    void CamerasManager::UnRegisterCamera(Camera *camera) {
        if (!Cameras.contains(camera)) return;
        auto cameraFlags = Cameras[camera];
        Cameras.erase(camera);
        RemoveAllEffectsFromCamera({camera, cameraFlags});
    }

    //endregion

    //region CameraEffects

    vector<ICameraEffect *> CamerasManager::CameraEffects = vector<ICameraEffect *>();

    void CamerasManager::RegisterCameraEffect(ICameraEffect *cameraEffect) {
        UnRegisterCameraEffect(cameraEffect);
        CameraEffects.push_back(cameraEffect);
        AddEffectToAllCameras(cameraEffect);
    }

    void CamerasManager::UnRegisterCameraEffect(ICameraEffect *cameraEffect) {
        auto position = find(CameraEffects.begin(), CameraEffects.end(), cameraEffect);
        if (position == CameraEffects.end()) return;

        CameraEffects.erase(position);
        RemoveEffectFromAllCameras(cameraEffect);
    }

    void CamerasManager::AddEffectToAllCameras(ICameraEffect *rb) {
        for (auto pair: Cameras) {
            RegisteredCamera rc = {pair.first, pair.second};
            if (!rb->IsSuitableForCamera(rc)) continue;
            rb->HandleAddedToCamera(rc);
        }
    }

    void CamerasManager::RemoveEffectFromAllCameras(ICameraEffect *rb) {
        for (auto pair: Cameras) {
            RegisteredCamera rc = {pair.first, pair.second};
            if (!rb->IsSuitableForCamera(rc)) continue;
            rb->HandleRemovedFromCamera(rc);
        }
    }

    void CamerasManager::AddAllEffectsToCamera(const RegisteredCamera &rc) {
        for (auto rb: CameraEffects) {
            if (!rb->IsSuitableForCamera(rc)) continue;
            rb->HandleAddedToCamera(rc);
        }
    }

    void CamerasManager::RemoveAllEffectsFromCamera(const RegisteredCamera &rc) {
        for (auto rb: CameraEffects) {
            if (!rb->IsSuitableForCamera(rc)) continue;
            rb->HandleRemovedFromCamera(rc);
        }
    }

    //endregion
}
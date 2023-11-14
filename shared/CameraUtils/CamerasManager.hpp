#pragma once

#include "CameraUtils/RegisteredCamera.hpp"
#include "CameraUtils/ICameraEffect.hpp"
#include "CameraUtils/CameraFlags.hpp"
#include "UnityEngine/Camera.hpp"
#include <vector>
#include <map>

namespace CameraUtils {
    class CamerasManager {
        //region Cameras

       private:
        static std::map<UnityEngine::Camera *, CameraFlags> Cameras;

       public:
        static void RegisterDesktopCamera(UnityEngine::Camera *camera, CameraFlags cameraFlags = CameraFlags::CF_None);

        static void RegisterHMDCamera(UnityEngine::Camera *camera, CameraFlags cameraFlags = CameraFlags::CF_None);

        static void RegisterMirrorCamera(UnityEngine::Camera *mirrorCamera, UnityEngine::Camera *currentCamera);

       private:
        static void RegisterCamera(UnityEngine::Camera *camera, CameraFlags cameraFlags);

       public:
        static void UnRegisterCamera(UnityEngine::Camera *camera);

        //endregion

        //region CameraEffects

       private:
        static std::vector<ICameraEffect *> CameraEffects;

       public:
        static void RegisterCameraEffect(ICameraEffect *cameraEffect);

        static void UnRegisterCameraEffect(ICameraEffect *cameraEffect);

       private:
        static void AddEffectToAllCameras(ICameraEffect *rb);

        static void RemoveEffectFromAllCameras(ICameraEffect *rb);

        static void AddAllEffectsToCamera(const RegisteredCamera &rc);

        static void RemoveAllEffectsFromCamera(const RegisteredCamera &rc);

        //endregion
    };
}
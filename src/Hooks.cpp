#include "include/Hooks.hpp"

#include "shared/CamerasManager.hpp"
#include "shared/VisibilityUtils.hpp"
#include "include/DelayedCameraRegistrator.hpp"

#include "beatsaber-hook/shared/utils/typedefs-string.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/MirrorRendererSO.hpp"
#include "GlobalNamespace/GameScenesManager.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/RenderTexture.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/Matrix4x4.hpp"
#include "UnityEngine/Rect.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace UnityEngine::SceneManagement;

namespace CameraUtils {
    //region ActivateScenePatch

    MAKE_HOOK_MATCH(
            GameScenesManager_ActivatePresentedSceneRootObjects,
            &GameScenesManager::ActivatePresentedSceneRootObjects,
            void,
            System::Collections::Generic::List_1<StringW> * scenesToPresent
    ) {
        GameScenesManager_ActivatePresentedSceneRootObjects(scenesToPresent);

        for (int i = 0; i < scenesToPresent->get_Count(); i++) {
            auto sceneName = scenesToPresent->get_Item(i);
            auto rootGameObjects = SceneManager::GetSceneByName(sceneName).GetRootGameObjects();

            for (int j = 0; j < rootGameObjects.size(); j++) {
                auto rootGO = rootGameObjects.get(j);
                auto cameras = rootGO->GetComponentsInChildren<Camera *>();

                for (int k = 0; k < cameras.size(); k++) {
                    auto camera = cameras.get(k);
                    VisibilityUtils::UpdateCameraIfKnown(camera);
                }
            }
        }
    }

    //endregion

    //region MirrorPatch

    MAKE_HOOK_MATCH(
            MirrorRendererSO_CreateOrUpdateMirrorCamera,
            &MirrorRendererSO::CreateOrUpdateMirrorCamera,
            void,
            MirrorRendererSO * self,
            Camera * currentCamera,
            RenderTexture * renderTexture
    ) {
        MirrorRendererSO_CreateOrUpdateMirrorCamera(self, currentCamera, renderTexture);
        CamerasManager::RegisterMirrorCamera(self->_mirrorCamera, currentCamera);
    }

    MAKE_HOOK_MATCH(
            MirrorRendererSO_RenderMirror,
            &MirrorRendererSO::RenderMirror,
            void,
            MirrorRendererSO * self,
            Vector3 camPosition,
            Quaternion camRotation,
            Matrix4x4 camProjectionMatrix,
            Rect screenRect,
            Vector3 reclectionPlanePos,
            Vector3 reflectionPlaneNormal
    ) {
        MirrorRendererSO_RenderMirror(
                self,
                camPosition,
                camRotation,
                camProjectionMatrix,
                screenRect,
                reclectionPlanePos,
                reflectionPlaneNormal
        );

        CamerasManager::UnRegisterCamera(self->_mirrorCamera);
    }

    //endregion

    //region OnGameplayCoreInstaller

    MAKE_HOOK_MATCH(
            OnGameplayCoreInstaller,
            &GameplayCoreInstaller::InstallBindings,
            void,
            GameplayCoreInstaller * self
    ) {
        OnGameplayCoreInstaller(self);
        auto root = self->get_transform();
        DelayedCameraRegistrator::Construct(root);
    }

    //endregion

    //region installHooks

    void InstallHooks(const Paper::ConstLoggerContext<12> &logger) {
        INSTALL_HOOK(logger, GameScenesManager_ActivatePresentedSceneRootObjects);
        INSTALL_HOOK(logger, MirrorRendererSO_CreateOrUpdateMirrorCamera);
        INSTALL_HOOK(logger, MirrorRendererSO_RenderMirror);
        INSTALL_HOOK(logger, OnGameplayCoreInstaller);
    }

    //endregion
}

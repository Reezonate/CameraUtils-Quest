#include "CameraUtils/VisibilityUtils.hpp"
#include "CameraUtils/EnumUtils.hpp"

using namespace UnityEngine;

namespace CameraUtils {
    //region SetLayer

    void VisibilityUtils::SetLayer(Transform *transform, VisibilityLayer layer) {
        SetLayer(transform->get_gameObject(), layer);
    }

    void VisibilityUtils::SetLayer(GameObject *gameObject, VisibilityLayer layer) {
        gameObject->set_layer((int) layer);
    }

    //endregion

    //region SetLayerRecursively

    void VisibilityUtils::SetLayerRecursively(GameObject *gameObject, VisibilityLayer layer) {
        SetLayerRecursively(gameObject->get_transform(), layer);
    }

    void VisibilityUtils::SetLayerRecursively(Transform *transform, VisibilityLayer layer) {
        transform->get_gameObject()->set_layer((int) layer);

        for (int i = 0; i < transform->get_childCount(); i++) {
            auto child = transform->GetChild(i);
            SetLayerRecursively(child, layer);
        }
    }

    //endregion

    //region GetOrAddRegistrator

    AutoCameraRegistrator *VisibilityUtils::GetOrAddCameraRegistrator(Camera *camera) {
        auto go = camera->get_gameObject();

        AutoCameraRegistrator *cameraRegistrator;

        if (!go->TryGetComponent<AutoCameraRegistrator *>(cameraRegistrator)) {
            cameraRegistrator = go->AddComponent<AutoCameraRegistrator *>();
        }

        return cameraRegistrator;
    }

    //endregion

    //region InternalUtils

    void VisibilityUtils::UpdateCameraIfKnown(Camera *camera) {
        auto name = camera->get_name();

        if (name == "MenuMainCamera" || name == "MainCamera" || name == "SmoothCamera") {
            auto cameraRegistrator = GetOrAddCameraRegistrator(camera);

            auto flags = cameraRegistrator->get_AdditionalFlags();
            flags |= CameraFlags::CF_FirstPerson;
            if (name == "SmoothCamera") {
                flags |= CameraFlags::CF_Composition;
            }
            cameraRegistrator->set_AdditionalFlags(flags);
        }
    }

    //endregion
}
#include "DelayedCameraRegistrator.hpp"
#include "UnityEngine/Camera.hpp"
#include "VisibilityUtils.hpp"

using namespace UnityEngine;

//region <----------- INTERNAL ---------------------------------------------------------------

namespace CameraUtils {
    //region Cpp_MonoBehavior

    Cpp_DelayedCameraRegistrator::Cpp_DelayedCameraRegistrator(
            UnityEngine::GameObject *go
    ) : gameObject(go) {}

    //endregion

    //region Update

    void Cpp_DelayedCameraRegistrator::Update() {
        if (_skippedFrames++ < 1) return;

        for (auto camera: Object::FindObjectsOfType<UnityEngine::Camera *>()) {
            VisibilityUtils::UpdateCameraIfKnown(camera);
        }

        Object::Destroy(gameObject);
    }

    //endregion
}

//endregion

//region  <----------- CODEGEN ------------------------------------------------------------------------------

DEFINE_TYPE(CameraUtils, DelayedCameraRegistrator);

namespace CameraUtils {
    void DelayedCameraRegistrator::Update() {
        cpp->Update();
    }

    void DelayedCameraRegistrator::OnDestroy() {
        delete cpp;
    }

    DelayedCameraRegistrator *DelayedCameraRegistrator::Construct(UnityEngine::Transform *parent) {
        auto gameObject = GameObject::New_ctor("DelayedCameraRegistrator");
        auto transform = gameObject->get_transform();
        transform->SetParent(parent, false);

        auto component = gameObject->AddComponent<DelayedCameraRegistrator *>();
        component->cpp = new Cpp_DelayedCameraRegistrator(gameObject);
        return component;
    }
}

//endregion
#pragma once

#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"

//region <----------- INTERNAL ---------------------------------------------------------------

namespace CameraUtils {
    class Cpp_DelayedCameraRegistrator {
        //region Cpp_MonoBehavior

        public:
        UnityEngine::GameObject *gameObject = nullptr;

        Cpp_DelayedCameraRegistrator(const Cpp_DelayedCameraRegistrator &other) = delete;

        explicit Cpp_DelayedCameraRegistrator(UnityEngine::GameObject *gameObject);

        //endregion

        //region Update

        private:
        int _skippedFrames = 0;

        public:
        void Update();

        //endregion
    };
}

//endregion

//region  <----------- CODEGEN ------------------------------------------------------------------------------

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(CameraUtils, DelayedCameraRegistrator, UnityEngine::MonoBehaviour) {
    DECLARE_INSTANCE_METHOD(void, Update);

    DECLARE_INSTANCE_METHOD(void, OnDestroy);

    public:
    Cpp_DelayedCameraRegistrator *cpp = nullptr;

    static DelayedCameraRegistrator *Construct(UnityEngine::Transform *parent);
};

//endregion

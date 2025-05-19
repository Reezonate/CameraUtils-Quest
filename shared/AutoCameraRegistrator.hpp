#pragma once

#include "CameraFlags.hpp"
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Camera.hpp"

//region <----------- INTERNAL ---------------------------------------------------------------

namespace CameraUtils {
    class Cpp_AutoCameraRegistrator {
        //region Cpp_MonoBehavior

        public:
        UnityEngine::GameObject *gameObject = nullptr;

        Cpp_AutoCameraRegistrator(const Cpp_AutoCameraRegistrator &other) = delete;

        explicit Cpp_AutoCameraRegistrator(UnityEngine::GameObject *go);

        //endregion

        //region CameraFlags

        private:
        CameraFlags _additionalFlags = CameraFlags::CF_None;

        public:
        [[nodiscard]] CameraFlags get_AdditionalFlags() const;

        void set_AdditionalFlags(CameraFlags value);

        //endregion

        //region Events

        private:
        UnityEngine::Camera *_camera = nullptr;
        bool _flagsDirty = true;
        int _lastCullingMask = 0;

        [[nodiscard]] inline bool get_IsDirty() const;

        public:
        void Awake();

        void OnDisable();

        void OnPreCull();

        //endregion

        //region Register / UnRegister

        private:
        void Register();

        void UnRegister();

        //endregion
    };
}

//endregion

//region  <----------- CODEGEN ------------------------------------------------------------------------------

DECLARE_CLASS_CODEGEN(CameraUtils, AutoCameraRegistrator, UnityEngine::MonoBehaviour) {
    DECLARE_INSTANCE_METHOD(void, Awake);

    DECLARE_INSTANCE_METHOD(void, OnDestroy);

    DECLARE_INSTANCE_METHOD(void, OnDisable);

    DECLARE_INSTANCE_METHOD(void, OnPreCull);

    private:
    Cpp_AutoCameraRegistrator *_internal = nullptr;

    public:
    [[nodiscard]] CameraFlags get_AdditionalFlags() const;

    void set_AdditionalFlags(CameraFlags value);
};

//endregion

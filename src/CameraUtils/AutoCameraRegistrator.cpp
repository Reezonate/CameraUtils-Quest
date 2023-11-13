#include "CameraUtils/AutoCameraRegistrator.hpp"
#include "CameraUtils/CamerasManager.hpp"

DEFINE_TYPE(CameraUtils, AutoCameraRegistrator);

using namespace UnityEngine;

namespace CameraUtils {
//region <----------- INTERNAL ---------------------------------------------------------------

    //region Cpp_MonoBehavior

    Cpp_AutoCameraRegistrator::Cpp_AutoCameraRegistrator(
            UnityEngine::GameObject *go
    ) : gameObject(go) {}

    //endregion

    //region CameraFlags

    CameraFlags Cpp_AutoCameraRegistrator::get_AdditionalFlags() const {
        return _additionalFlags;
    }

    void Cpp_AutoCameraRegistrator::set_AdditionalFlags(CameraFlags value) {
        _additionalFlags = value;
        _flagsDirty = true;
    }

    //endregion

    //region Events

    bool Cpp_AutoCameraRegistrator::get_IsDirty() const {
        return _flagsDirty || _camera->get_cullingMask() != _lastCullingMask;
    }

    void Cpp_AutoCameraRegistrator::Awake() {
        _camera = gameObject->GetComponent<Camera *>();
    }

    void Cpp_AutoCameraRegistrator::OnDisable() {
        UnRegister();
        _flagsDirty = true;
    }

    void Cpp_AutoCameraRegistrator::OnPreCull() {
        if (!get_IsDirty()) return;
        Register();
        _lastCullingMask = _camera->get_cullingMask();
        _flagsDirty = false;
    }

    //endregion

    //region Register / UnRegister

    void Cpp_AutoCameraRegistrator::Register() {
        if (_camera->get_stereoEnabled()) {
            CamerasManager::RegisterHMDCamera(_camera, _additionalFlags);
        } else {
            CamerasManager::RegisterDesktopCamera(_camera, _additionalFlags);
        }
    }

    void Cpp_AutoCameraRegistrator::UnRegister() {
        CamerasManager::UnRegisterCamera(_camera);
    }

    //endregion

//endregion

//region  <----------- CODEGEN ------------------------------------------------------------------------------

    void AutoCameraRegistrator::Awake() {
        _internal = new Cpp_AutoCameraRegistrator(get_gameObject());
        _internal->Awake();
    }

    void AutoCameraRegistrator::OnDestroy() {
        delete _internal;
    }

    void AutoCameraRegistrator::OnDisable() {
        _internal->OnDisable();
    }

    void AutoCameraRegistrator::OnPreCull() {
        _internal->OnPreCull();
    }

    CameraFlags AutoCameraRegistrator::get_AdditionalFlags() const {
        return _internal->get_AdditionalFlags();
    }

    void AutoCameraRegistrator::set_AdditionalFlags(CameraFlags value) {
        _internal->set_AdditionalFlags(value);
    }

//endregion
}
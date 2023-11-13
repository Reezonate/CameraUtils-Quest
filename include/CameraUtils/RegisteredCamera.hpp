#pragma once

#include "UnityEngine/Camera.hpp"
#include "CameraUtils/CameraFlags.hpp"

namespace CameraUtils {
    struct RegisteredCamera {
        UnityEngine::Camera *camera = nullptr;
        CameraFlags cameraFlags = CameraFlags::CF_None;
    };
}
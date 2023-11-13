#pragma once

#include "CameraUtils/RegisteredCamera.hpp"

namespace CameraUtils {
    class ICameraEffect {
       public:
        virtual bool IsSuitableForCamera(const RegisteredCamera &registeredCamera) = 0;

        virtual void HandleAddedToCamera(const RegisteredCamera &registeredCamera) = 0;

        virtual void HandleRemovedFromCamera(const RegisteredCamera &registeredCamera) = 0;
    };
}
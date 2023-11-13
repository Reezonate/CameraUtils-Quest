#pragma once

#include "custom-types/shared/macros.hpp"

namespace CameraUtils {
    enum CameraFlags {
        CF_None = 0,
        CF_Desktop = 1,
        CF_HMD = 2,
        CF_Mirror = 4,
        CF_FirstPerson = 8,
        CF_ThirdPerson = 16,
        CF_Composition = 32,
    };
}
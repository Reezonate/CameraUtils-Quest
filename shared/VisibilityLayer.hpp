#pragma once

#include "custom-types/shared/macros.hpp"

namespace CameraUtils {
    enum VisibilityLayer {
        VL_Default = 0,
        VL_TransparentFX = 1,
        VL_IgnoreRaycast = 2,
        VL_ThirdPerson = 3, //<----------- Possibly used by Unity (see: https://docs.unity3d.com/ScriptReference/GameObject-layer.html)
        VL_Water = 4,
        VL_UI = 5,
        VL_FirstPerson = 6, //<----------- Not used in Vanilla
        VL_Layer7 = 7, //<----------- Not used in Vanilla
        VL_Note = 8,
        VL_NoteDebris = 9,
        VL_Avatar = 10,
        VL_Obstacle = 11,
        VL_Saber = 12,
        VL_NeonLight = 13,
        VL_Environment = 14,
        VL_GrabPassTexture1 = 15,
        VL_CutEffectParticles = 16,
        VL_HmdOnly = 17, //<----------- Not used in Vanilla
        VL_DesktopOnly = 18, //<----------- Not used in Vanilla
        VL_NonReflectedParticles = 19,
        VL_EnvironmentPhysics = 20,
        VL_AlwaysVisible = 21, //<----------- Not used in Vanilla
        VL_Event = 22,
        VL_DesktopOnlyAndReflected = 23, //<----------- Not used in Vanilla
        VL_HmdOnlyAndReflected = 24, //<----------- Not used in Vanilla
        VL_FixMRAlpha = 25,
        VL_AlwaysVisibleAndReflected = 26, //<----------- Not used in Vanilla
        VL_DontShowInExternalMRCamera = 27,
        VL_PlayersPlace = 28,
        VL_Skybox = 29,
        VL_MRForegroundClipPlane = 30,
        VL_Reserved = 31,
    };
}
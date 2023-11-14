#pragma once

#include "UnityEngine/Camera.hpp"

namespace CameraUtils {
    class CullingMaskUtils {
        //region Constants

       public:
        static const int Nothing;
        static const int Everything;

        static const int MirrorMask_OR;
        static const int MirrorMask_AND;

        static const int HMDMask_OR;
        static const int HMDMask_AND;

        static const int DesktopMask_OR;
        static const int DesktopMask_AND;

        //endregion

        //region SetupMirrorCamera

       public:
        static void SetupMirrorCamera(UnityEngine::Camera *mirrorCamera, UnityEngine::Camera *currentCamera);

        //endregion

        //region SetupHMDCamera

       public:
        static void SetupHMDCamera(UnityEngine::Camera *camera);

        //endregion

        //region SetupDesktopCamera

       public:
        static void SetupDesktopCamera(UnityEngine::Camera *camera);

        //endregion
    };
}
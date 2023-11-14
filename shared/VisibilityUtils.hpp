#pragma once

#include "VisibilityLayer.hpp"
#include "AutoCameraRegistrator.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Camera.hpp"

namespace CameraUtils {
    class VisibilityUtils {
        //region SetLayer

       public:
        static void SetLayer(UnityEngine::Transform *transform, VisibilityLayer layer);

        static void SetLayer(UnityEngine::GameObject *gameObject, VisibilityLayer layer);

        //endregion

        //region SetLayerRecursively

       public:
        static void SetLayerRecursively(UnityEngine::GameObject *gameObject, VisibilityLayer layer);

        static void SetLayerRecursively(UnityEngine::Transform *transform, VisibilityLayer layer);

        //endregion

        //region GetOrAddRegistrator

       public:
        static AutoCameraRegistrator *GetOrAddCameraRegistrator(UnityEngine::Camera *camera);

        //endregion

        //region InternalUtils

       public:
        static void UpdateCameraIfKnown(UnityEngine::Camera *camera);

        //endregion
    };
}
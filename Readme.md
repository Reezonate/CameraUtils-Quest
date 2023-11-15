# CameraUtils for Quest
Beat Saber modding library that standardizes the use of GameObject layers and provides tools for easier rendering pipeline modifications

- [**PC Version**](https://github.com/Reezonate/CameraUtils)

## Adding as a dependency
```
qpm dependency add camera-utils
```

### HMD-only rendering
```c
#include "camera-utils/shared/VisibilityUtils.hpp"

void HmdOnlyExample::Awake() {
    VisibilityUtils::SetLayerRecursively(gameObject, CameraUtils::VisibilityLayer::VL_HmdOnlyAndReflected);
    //If you don't want object to be rendered in reflections, use VisibilityLayer::VL_HmdOnly
}
```

### Desktop-only rendering
```c
#include "camera-utils/shared/VisibilityUtils.hpp"

void DesktopOnlyExample::Awake() {
    VisibilityUtils::SetLayerRecursively(gameObject, CameraUtils::VisibilityLayer::VL_DesktopOnlyAndReflected);
    //If you don't want object to be rendered in reflections, use VisibilityLayer::VL_DesktopOnly
}
```

### Registering custom Camera
- To add your camera to the system, simply call `CameraUtils::CamerasManager::RegisterDesktopCamera(yourCamera)`
- Make sure to remove your camera on destroy, using `CameraUtils::CamerasManager::UnRegisterCamera(yourCamera)`
- Alternatively, you can just add `CameraUtils::AutoCameraRegistrator` component to the Camera's GameObject
```c
#include "camera-utils/shared/AutoCameraRegistrator.hpp"

void InitCamera(UnityEngine::Camera *camera) {
    camera->get_gameObject()->AddComponent<CameraUtils::AutoCameraRegistrator *>();
}
```

### Registering CameraEffect
- To insert custom logic into the render pipeline, use `CameraUtils::CamerasManager::RegisterCameraEffect()`
- Make sure to remove your effects on dispose, using `CameraUtils::CamerasManager::UnRegisterCameraEffect()`

See: [simple Post-Process effect example **(!PC Version!)**](https://github.com/Reezonate/CameraUtilsSandbox/blob/master/CameraUtilsSandbox%20Plugin/Source/Core/PostProcessDemo.cs)

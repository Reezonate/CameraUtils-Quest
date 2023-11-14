#include "shared/CullingMaskUtils.hpp"
#include "shared/VisibilityLayer.hpp"

using namespace UnityEngine;
using namespace CameraUtils;

namespace CameraUtils {
    //region Constants

    const int CullingMaskUtils::Nothing = 0;
    const int CullingMaskUtils::Everything = 2147483647;

    const int CullingMaskUtils::MirrorMask_OR =
            Nothing |
            (1 << (int) VisibilityLayer::VL_AlwaysVisibleAndReflected) |
            (1 << (int) VisibilityLayer::VL_DesktopOnlyAndReflected) |
            (1 << (int) VisibilityLayer::VL_HmdOnlyAndReflected);

    const int CullingMaskUtils::MirrorMask_AND =
            Everything &
            ~(1 << (int) VisibilityLayer::VL_AlwaysVisible) &
            ~(1 << (int) VisibilityLayer::VL_DesktopOnly) &
            ~(1 << (int) VisibilityLayer::VL_HmdOnly);

    const int CullingMaskUtils::HMDMask_OR =
            Nothing |
            (1 << (int) VisibilityLayer::VL_AlwaysVisible) |
            (1 << (int) VisibilityLayer::VL_AlwaysVisibleAndReflected) |
            (1 << (int) VisibilityLayer::VL_HmdOnly) |
            (1 << (int) VisibilityLayer::VL_HmdOnlyAndReflected);

    const int CullingMaskUtils::HMDMask_AND =
            Everything &
            ~(1 << (int) VisibilityLayer::VL_DesktopOnly) &
            ~(1 << (int) VisibilityLayer::VL_DesktopOnlyAndReflected);

    const int CullingMaskUtils::DesktopMask_OR =
            Nothing |
            (1 << (int) VisibilityLayer::VL_AlwaysVisible) |
            (1 << (int) VisibilityLayer::VL_AlwaysVisibleAndReflected) |
            (1 << (int) VisibilityLayer::VL_DesktopOnly) |
            (1 << (int) VisibilityLayer::VL_DesktopOnlyAndReflected);

    const int CullingMaskUtils::DesktopMask_AND =
            Everything &
            ~(1 << (int) VisibilityLayer::VL_HmdOnly) &
            ~(1 << (int) VisibilityLayer::VL_HmdOnlyAndReflected);

    //endregion

    //region SetupMirrorCamera

    void CullingMaskUtils::SetupMirrorCamera(Camera *mirrorCamera, Camera *currentCamera) {
        auto cullingMask = mirrorCamera->get_cullingMask();
        cullingMask |= MirrorMask_OR;
        cullingMask &= MirrorMask_AND;
        cullingMask &= currentCamera->get_cullingMask();
        mirrorCamera->set_cullingMask(cullingMask);
    }

    //endregion

    //region SetupHMDCamera

    void CullingMaskUtils::SetupHMDCamera(Camera *camera) {
        auto cullingMask = camera->get_cullingMask();
        cullingMask |= HMDMask_OR;
        cullingMask &= HMDMask_AND;
        camera->set_cullingMask(cullingMask);
    }

    //endregion

    //region SetupDesktopCamera

    void CullingMaskUtils::SetupDesktopCamera(Camera *camera) {
        auto cullingMask = camera->get_cullingMask();
        cullingMask |= DesktopMask_OR;
        cullingMask &= DesktopMask_AND;
        camera->set_cullingMask(cullingMask);
    }

    //endregion
}
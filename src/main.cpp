#include "main.hpp"

#include "scotland2/shared/loader.hpp"
#include "include/Hooks.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "custom-types/shared/register.hpp"

using namespace CameraUtils;

inline modloader::ModInfo modInfo = {MOD_ID, VERSION, 0};

namespace CameraUtils {
    Paper::ConstLoggerContext<12> Main::Logger = Paper::ConstLoggerContext("CameraUtils");
}

extern "C" void setup(CModInfo *info) {
    *info = modInfo.to_c();
    Paper::Logger::RegisterFileContextId(Main::Logger.tag);
}

extern "C" void late_load() {
    il2cpp_functions::Init();
    custom_types::Register::AutoRegister();
    CameraUtils::InstallHooks(Main::Logger);
}
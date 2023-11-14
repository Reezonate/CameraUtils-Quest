#include "main.hpp"

#include "include/Hooks.hpp"
#include "modloader/shared/modloader.hpp"
#include "custom-types/shared/macros.hpp"

using namespace CameraUtils;

static ModInfo modInfo;

Logger &getLogger() {
    static auto *logger = new Logger(modInfo);
    return *logger;
}

extern "C" void setup(ModInfo &info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
}

extern "C" void load() {
    il2cpp_functions::Init();
    custom_types::Register::AutoRegister();
    CameraUtils::InstallHooks(getLogger());
}
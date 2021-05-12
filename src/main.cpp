#include "main.hpp"
#include "ITweak.hpp"

#include "Tweaks/NoNames.hpp"
#include "Tweaks/NoPromo.hpp"

#include "UI/SettingsFlowCoordinator.hpp"
#include "UI/MainSettingsViewController.hpp"
#include "UI/NavigationViewController.hpp"

#include "questui/shared/QuestUI.hpp"
#include "custom-types/shared/register.hpp"

#include <list>

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;

    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

std::list<Tweakaroo::ITweak*> tweaks = {
    new Tweakaroo::Tweaks::NoNames(),
    new Tweakaroo::Tweaks::NoPromo()
};

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    // Install our hooks (none defined yet)

    for (Tweakaroo::ITweak* tweak : tweaks) {
        tweak->CreateJSONConfig();
        tweak->InstallHooks();
    }

    custom_types::Register::RegisterTypes<
        Tweakaroo::SettingsFlowCoordinator,
        Tweakaroo::MainSettingsViewController,
        Tweakaroo::NavigationViewController
    >();

    QuestUI::Register::RegisterModSettingsFlowCoordinator<Tweakaroo::SettingsFlowCoordinator*>(modInfo);
    getLogger().info("Installed all hooks!");
}
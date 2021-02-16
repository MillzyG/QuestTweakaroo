#include "main.hpp"

#include "GlobalNamespace/PromoViewController.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
    #include "LevelBar.hpp"
        #include "TMPro/TextMeshProUGUI.hpp"

#include "UnityEngine/GameObject.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/utils.h"

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

// I'm Not Interested
MAKE_HOOK_OFFSETLESS(PromoViewController_DidActivate, void,
    GlobalNamespace::PromoViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling
) {
PromoViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

//  if ("Hide DLC Promo" is toggled on) {
        self->get_gameObject()->SetActive(false);
//  }
}

// No Names
MAKE_HOOK_OFFSETLESS(PauseMenuManager_ShowMenu, void,
    GlobalNamespace::PauseMenuManager* self
) {
    PauseMenuManager_ShowMenu(self);
//  if ("No Names" is toggled on) {
    self->levelBar->authorNameText->get_gameObject()->SetActive(false);
//  }
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    INSTALL_HOOK_OFFSETLESS(getLogger(), PromoViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "PromoViewController", "DidActivate", 3));

    getLogger().info("Installing hooks...");
    // Install our hooks (none defined yet)
    getLogger().info("Installed all hooks!");
}
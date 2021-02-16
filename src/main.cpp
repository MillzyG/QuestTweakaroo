#include "main.hpp"

#include "GlobalNamespace/PromoViewController.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/LevelBar.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"

#include "TMPro/TextMeshProUGUI.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "TMPro/TextMeshProUGUI.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/utils.h"

#include "questui/shared/QuestUI.hpp"
#include "custom-types/shared/register.hpp"
#include "SettingsViewContoller.hpp"


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


//RGB Menu
MAKE_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, void,
    GlobalNamespace::MainMenuViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling
) {
    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    auto* solo_button = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("SoloButton"));
    auto* solo_text = solo_button->get_gameObject()->GetComponentInChildren<TMPro::TextMeshProUGUI*>();


    UnityEngine::Color textColour = UnityEngine::Color(getConfig().config["textR"].GetFloat(), getConfig().config["textG"].GetFloat(), getConfig().config["textB"].GetFloat(), 1);

    solo_text->set_color(textColour);
}

// I'm Not Interested
MAKE_HOOK_OFFSETLESS(PromoViewController_DidActivate, void,
    GlobalNamespace::PromoViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling
) {
PromoViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    if (getConfig().config["promo"] == true) {
        self->get_gameObject()->SetActive(false);
    }
}

// No Names
MAKE_HOOK_OFFSETLESS(PauseMenuManager_ShowMenu, void,
    GlobalNamespace::PauseMenuManager* self
) {
    PauseMenuManager_ShowMenu(self);
    if (getConfig().config["names"] == true) {
        self->levelBar->authorNameText->get_gameObject()->SetActive(false);
    }
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
    getLogger().info("Completed setup!");

    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();
    if (!getConfig().config.HasMember("promo")) {
        getConfig().config.AddMember("promo", rapidjson::Value(0).SetBool(true), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("names")) {
        getConfig().config.AddMember("names", rapidjson::Value(0).SetBool(false), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("textR")) {
        getConfig().config.AddMember("textR", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("textG")) {
        getConfig().config.AddMember("textG", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("textB")) {
        getConfig().config.AddMember("textB", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    INSTALL_HOOK_OFFSETLESS(getLogger(), PromoViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "PromoViewController", "DidActivate", 3));
    INSTALL_HOOK_OFFSETLESS(getLogger(), PauseMenuManager_ShowMenu, il2cpp_utils::FindMethodUnsafe("", "PauseMenuManager", "ShowMenu", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), MainMenuViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "DidActivate", 3));

    getLogger().info("Installing hooks...");
    // Install our hooks (none defined yet)
    custom_types::Register::RegisterType<Tweakaroo::SettingsViewController>();
    QuestUI::Register::RegisterModSettingsViewController<Tweakaroo::SettingsViewController*>(modInfo);
    getLogger().info("Installed all hooks!");
}
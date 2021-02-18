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


MAKE_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, void,
    GlobalNamespace::MainMenuViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling
) {
    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

        auto* solo_button = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("SoloButton"));
        auto* solo_text = solo_button->get_gameObject()->GetComponentInChildren<TMPro::TextMeshProUGUI*>();

        auto* campaign_button =  UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("CampaignButton"));
        auto* campaign_text = campaign_button->get_gameObject()->GetComponentInChildren<TMPro::TextMeshProUGUI*>();

        auto* party_button =  UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("PartyButton"));
        auto* party_text = party_button->get_gameObject()->GetComponentInChildren<TMPro::TextMeshProUGUI*>();

        auto* online_button =  UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("OnlineButton"));
        auto* online_text = party_button->get_gameObject()->GetComponentInChildren<TMPro::TextMeshProUGUI*>();

        

    // RGB MENU
    if (getConfig().config["color"] == true) {

        UnityEngine::Color solo_textColour = UnityEngine::Color(getConfig().config["soloR"].GetFloat(), getConfig().config["soloG"].GetFloat(), getConfig().config["soloB"].GetFloat(), 1);
        UnityEngine::Color campaign_textColour = UnityEngine::Color(getConfig().config["campaignR"].GetFloat(), getConfig().config["campaignG"].GetFloat(), getConfig().config["campaignB"].GetFloat(), 1);
        UnityEngine::Color party_textColour = UnityEngine::Color(getConfig().config["partyR"].GetFloat(), getConfig().config["partyG"].GetFloat(), getConfig().config["partyB"].GetFloat(), 1);
        UnityEngine::Color online_textColour = UnityEngine::Color(getConfig().config["onlineR"].GetFloat(), getConfig().config["onlineG"].GetFloat(), getConfig().config["onlineB"].GetFloat(), 1);

        solo_text->set_color(solo_textColour);
        campaign_text->set_color(campaign_textColour);
        party_text->set_color(party_textColour);
        online_text->set_color(online_textColour);

    } else {

        solo_text->set_color(UnityEngine::Color::get_white());
        campaign_text->set_color(UnityEngine::Color::get_white());
        party_text->set_color(UnityEngine::Color::get_white());
        online_text->set_color(UnityEngine::Color::get_white());
        
    }

    // VOID MENU ENVIRONMENT
    if (getConfig().config["voidMenu"] == true ){
        UnityEngine::GameObject::Instantiate(UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("Logo")));
        UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("MenuEnvironment"))->SetActive(false);
    }
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
        getConfig().config.AddMember("promo", rapidjson::Value(0).SetBool(false), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("names")) {
        getConfig().config.AddMember("names", rapidjson::Value(0).SetBool(false), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("color")) {
        getConfig().config.AddMember("color", rapidjson::Value(0).SetBool(false), allocator);
        getConfig().Write();
    }


    //Colors
    //solo
    if (!getConfig().config.HasMember("soloR")) {
        getConfig().config.AddMember("soloR", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("soloG")) {
        getConfig().config.AddMember("textG", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("soloB")) {
        getConfig().config.AddMember("soloB", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    //campaign
    if (!getConfig().config.HasMember("campaignR")) {
        getConfig().config.AddMember("campaignR", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("campaignG")) {
        getConfig().config.AddMember("campaignG", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("campaignB")) {
        getConfig().config.AddMember("campaignB", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    //party
    if (!getConfig().config.HasMember("partyR")) {
        getConfig().config.AddMember("partyR", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("partyG")) {
        getConfig().config.AddMember("partyG", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("partyB")) {
        getConfig().config.AddMember("partyB", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    //online
    if (!getConfig().config.HasMember("onlineR")) {
        getConfig().config.AddMember("onlineR", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("onlineG")) {
        getConfig().config.AddMember("onlineG", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }
    if (!getConfig().config.HasMember("onlineB")) {
        getConfig().config.AddMember("onlineB", rapidjson::Value(0).SetFloat(1), allocator);
        getConfig().Write();
    }

    // Void Menu
    if (!getConfig().config.HasMember("voidMenu")) {
        getConfig().config.AddMember("voidMenu", rapidjson::Value(0).SetBool(false), allocator);
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
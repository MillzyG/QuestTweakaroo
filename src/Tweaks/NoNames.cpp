#include "main.hpp"
#include "UI/MainSettingsViewController.hpp"
using namespace Tweakaroo::MainSettingsConfig;

#include "Tweaks/NoNames.hpp"
using namespace Tweakaroo::Tweaks;

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"

#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/LevelBar.hpp"

#include "TMPro/TextMeshProUGUI.hpp"
using namespace TMPro;

NoNames::NoNames() {}

TMPro::TextMeshProUGUI* noNamesTitle;
TMPro::TextMeshProUGUI* noNamesDesc;

UnityEngine::UI::Toggle* noNamesEnabled;

void NoNames::CreateConfig(UnityEngine::Transform* parent) {
    noNamesTitle = BeatSaberUI::CreateText(parent, GetName());
    noNamesTitle->set_fontSize(6.0f);
    noNamesTitle->set_alignment(TMPro::TextAlignmentOptions::Midline);

    noNamesDesc = BeatSaberUI::CreateText(parent, "Removes the Song Mapper/Artist from the\nPause Menu's LevelBar.");
    noNamesDesc->set_color(UnityEngine::Color::get_gray());
    noNamesDesc->set_fontSize(4.5f);
    noNamesDesc->set_alignment(TextAlignmentOptions::Midline);

    noNamesEnabled = BeatSaberUI::CreateToggle(parent, "Enabled", getConfig().config["NoNames"]["enabled"].GetBool(), 
        [](bool value) {
            getConfig().config["NoNames"]["enabled"].SetBool(value);
        }
    );
}

void NoNames::CreateJSONConfig() {
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();

    if (!getConfig().config.HasMember("NoNames")) {
        rapidjson::Value newObj(rapidjson::kObjectType);

        newObj.AddMember("enabled", rapidjson::Value(0).SetBool(false), allocator);
        getConfig().config.AddMember("NoNames", newObj, allocator);
    }

    if (!getConfig().config["NoNames"].HasMember("enabled")) {
        getConfig().config["NoNames"].AddMember("enabled", rapidjson::Value(0).SetBool(false), allocator);
    }

    getConfig().Write();
}

MAKE_HOOK_OFFSETLESS(PauseMenuManager_ShowMenu, void,
    GlobalNamespace::PauseMenuManager* self
) {
    self->levelBar->authorNameText->get_gameObject()->SetActive(false);
    PauseMenuManager_ShowMenu(self);
}

void NoNames::InstallHooks() {
    INSTALL_HOOK_OFFSETLESS(getLogger(), PauseMenuManager_ShowMenu, il2cpp_utils::FindMethodUnsafe("", "PauseMenuManager", "ShowMenu", 0));
}

std::string NoNames::GetName() {
    return "No Names";
}
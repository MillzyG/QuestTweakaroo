#include "main.hpp"
#include "UI/MainSettingsViewController.hpp"
using namespace Tweakaroo::MainSettingsConfig;

#include "Tweaks/NoPromo.hpp"
using namespace Tweakaroo::Tweaks;

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"

#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/MusicPackPromoBanner.hpp"

#include "TMPro/TextMeshProUGUI.hpp"
using namespace TMPro;

NoPromo::NoPromo() {}

TMPro::TextMeshProUGUI* noPromoTitle;
TMPro::TextMeshProUGUI* noPromoDesc;

UnityEngine::UI::Toggle* noPromoEnabled;

void NoPromo::CreateConfig(UnityEngine::Transform* parent) {
    noPromoTitle = BeatSaberUI::CreateText(parent, GetName());
    noPromoTitle->set_fontSize(6.0f);
    noPromoTitle->set_alignment(TMPro::TextAlignmentOptions::Midline);

    noPromoDesc = BeatSaberUI::CreateText(parent, "Removes the Music Pack Promo\nfrom the Main Menu.");
    noPromoDesc->set_color(UnityEngine::Color::get_gray());
    noPromoDesc->set_fontSize(4.5f);
    noPromoDesc->set_alignment(TextAlignmentOptions::Midline);

    noPromoEnabled = BeatSaberUI::CreateToggle(parent, "Enabled", getConfig().config["NoPromo"]["enabled"].GetBool(), 
        [](bool value) {
            getConfig().config["NoPromo"]["enabled"].SetBool(value);
        }
    );
}

void NoPromo::CreateJSONConfig() {
        rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();

    if (!getConfig().config.HasMember("NoPromo")) {
        rapidjson::Value newObj(rapidjson::kObjectType);

        newObj.AddMember("enabled", rapidjson::Value(0).SetBool(false), allocator);
        getConfig().config.AddMember("NoPromo", newObj, allocator);
    }

    if (!getConfig().config["NoPromo"].HasMember("enabled")) {
        getConfig().config["NoPromo"].AddMember("enabled", rapidjson::Value(0).SetBool(false), allocator);
    }

    getConfig().Write();
}

MAKE_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, void, 
    GlobalNamespace::MainMenuViewController* self, bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling
) {
    if (firstActivation && getConfig().config["NoPromo"]["enabled"].GetBool()) {
        self->musicPackPromoBanner->get_gameObject()->SetActive(false);
    }
}

void NoPromo::InstallHooks() {
    INSTALL_HOOK_OFFSETLESS(getLogger(), MainMenuViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "DidActivate", 3));
}

std::string NoPromo::GetName() {
    return "No Promo";
}
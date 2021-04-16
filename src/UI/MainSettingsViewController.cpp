#include "main.hpp"
#include "UI/MainSettingsViewController.hpp"
#include "UI/SettingsFlowCoordinator.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"
using namespace QuestUI;

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/GridLayoutGroup.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/UI/Button.hpp"

#include "TMPro/TextMeshProUGUI.hpp"
#include "TMPro/FontStyles.hpp"
#include "TMPro/TextAlignmentOptions.hpp"
using namespace TMPro;

#include "HMUI/ViewController_AnimationType.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"

DEFINE_TYPE(Tweakaroo::MainSettingsViewController);

UnityEngine::GameObject* mainContainer;

TextMeshProUGUI* mainTitle;
TextMeshProUGUI* mainDescription;

UnityEngine::UI::Toggle* toggle1 = nullptr;

void applyStyling() {
    mainTitle->set_fontSize(6.0f);
    mainTitle->set_alignment(TextAlignmentOptions::Midline);

    mainDescription->set_color(UnityEngine::Color::get_gray());
    mainDescription->set_fontSize(4.5f);
    mainDescription->set_alignment(TextAlignmentOptions::Midline);
}

void Tweakaroo::MainSettingsConfig::resetView() {
    UnityEngine::GameObject::Destroy(mainTitle->get_gameObject());
    UnityEngine::GameObject::Destroy(mainDescription->get_gameObject());
    
    if (toggle1 != nullptr) {
        UnityEngine::GameObject::Destroy(toggle1->get_transform()->get_parent()->get_gameObject());
    }
}

void Tweakaroo::MainSettingsConfig::noPromoConfig() {
    resetView();

    mainTitle = BeatSaberUI::CreateText(mainContainer->get_transform(), "No Promo");
    mainDescription = BeatSaberUI::CreateText(mainContainer->get_transform(), "Removes the Promo View Controller from the Main menu.");

    toggle1 = BeatSaberUI::CreateToggle(mainContainer->get_transform(), "Enable No Promo", getConfig().config["noPromoEnabled"].GetBool(),
        [](bool value) {
            getConfig().config["noPromoEnabled"].SetBool(value);
        }
    );

    applyStyling();
}

void Tweakaroo::MainSettingsConfig::noNamesConfig() {
    resetView();

    mainTitle = BeatSaberUI::CreateText(mainContainer->get_transform(), "No Names");
    mainDescription = BeatSaberUI::CreateText(mainContainer->get_transform(), "Removes the Author Name Text from the level bar in the pause menu.");

    toggle1 = BeatSaberUI::CreateToggle(mainContainer->get_transform(), "Enable No Names", getConfig().config["noNamesEnabled"].GetBool(),
        [](bool value) {
            getConfig().config["noNamesEnabled"].SetBool(value);
        }
    );
}

void Tweakaroo::MainSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;

    mainContainer = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

    mainTitle = BeatSaberUI::CreateText(mainContainer->get_transform(), "Tweakaroo 2.0.0 for BeatSaber 1.14.0");
    mainTitle->set_fontSize(6.0f);
    mainTitle->set_alignment(TextAlignmentOptions::Midline);

    mainDescription = BeatSaberUI::CreateText(mainContainer->get_transform(), "Tweakaroo is a \"compilation\" of minor tweaks and\nmods too small to deserve their own mod.");
    mainDescription->set_color(UnityEngine::Color::get_gray());
    mainDescription->set_fontSize(4.5f);
    mainDescription->set_alignment(TextAlignmentOptions::Midline);


}
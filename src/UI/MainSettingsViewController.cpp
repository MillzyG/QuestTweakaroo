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

UnityEngine::Transform* transform;

UnityEngine::UI::Toggle* toggle1 = nullptr;

void applyStyling() {
    mainTitle->set_fontSize(6.0f);
    mainTitle->set_alignment(TextAlignmentOptions::Midline);

    mainDescription->set_color(UnityEngine::Color::get_gray());
    mainDescription->set_fontSize(4.5f);
    mainDescription->set_alignment(TextAlignmentOptions::Midline);
}

void Tweakaroo::MainSettingsConfig::resetView() {
    UnityEngine::GameObject::Destroy(mainContainer);
    mainContainer = nullptr;
    mainContainer = BeatSaberUI::CreateScrollableSettingsContainer(transform);
}

UnityEngine::GameObject* Tweakaroo::MainSettingsConfig::getMainContainer() {
    return mainContainer;
}

void Tweakaroo::MainSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;

    transform = get_transform();
    mainContainer = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

    mainTitle = BeatSaberUI::CreateText(mainContainer->get_transform(), "Tweakaroo 2.0.0 for BeatSaber 1.14.0");
    mainTitle->set_fontSize(6.0f);
    mainTitle->set_alignment(TextAlignmentOptions::Midline);

    mainDescription = BeatSaberUI::CreateText(mainContainer->get_transform(), "Tweakaroo is a \"compilation\" of minor tweaks and\nmods too small to deserve their own mod.");
    mainDescription->set_color(UnityEngine::Color::get_gray());
    mainDescription->set_fontSize(4.5f);
    mainDescription->set_alignment(TextAlignmentOptions::Midline);
}
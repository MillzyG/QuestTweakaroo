#include "main.hpp"
#include "UI/NavigationViewController.hpp"
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

DEFINE_TYPE(Tweakaroo::NavigationViewController);

UnityEngine::GameObject* navContainer;

TextMeshProUGUI* navTitle;

UnityEngine::UI::Button* energyPercentage;
UnityEngine::UI::Button* noPromo;
UnityEngine::UI::Button* noNames;
UnityEngine::UI::Button* RGBMenu;
UnityEngine::UI::Button* voidMenuEnv;

void Tweakaroo::NavigationViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;

    navContainer = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

    navTitle = BeatSaberUI::CreateText(navContainer->get_transform(), "Tweaks");
    navTitle->set_fontSize(6.0f);
    navTitle->set_alignment(TextAlignmentOptions::Midline);

    energyPercentage = BeatSaberUI::CreateUIButton(navContainer->get_transform(), "Energy Percentage",
        []() {

        }
    );

    noPromo = BeatSaberUI::CreateUIButton(navContainer->get_transform(), "No Promo",
        []() {
            Tweakaroo::MainSettingsConfig::noPromoConfig();
        }
    );

    noNames = BeatSaberUI::CreateUIButton(navContainer->get_transform(), "No Names",
        []() {
            Tweakaroo::MainSettingsConfig::noNamesConfig();
        }
    );

    RGBMenu = BeatSaberUI::CreateUIButton(navContainer->get_transform(), "RGB Menu",
        []() {

        }
    );

    voidMenuEnv = BeatSaberUI::CreateUIButton(navContainer->get_transform(), "Void Menu Env", 
        []() {

        }
    );
}
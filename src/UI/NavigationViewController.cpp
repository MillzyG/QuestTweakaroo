#include "main.hpp"
#include "ITweak.hpp"
#include "UI/NavigationViewController.hpp"
#include "UI/SettingsFlowCoordinator.hpp"
using namespace Tweakaroo::MainSettingsConfig;

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

void Tweakaroo::NavigationViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;

    navContainer = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
    navContainer->get_transform()->set_localPosition(UnityEngine::Vector3(15.0f, 0.0f, 0.0f));

    navTitle = BeatSaberUI::CreateText(navContainer->get_transform(), "Tweaks");
    navTitle->set_fontSize(6.0f);
    navTitle->set_alignment(TextAlignmentOptions::Midline);

    for (ITweak* tweak : tweaks) {
        BeatSaberUI::CreateUIButton(navContainer->get_transform(), tweak->GetName(), 
            [tweak]{
                resetView();
                tweak->CreateConfig(getMainContainer()->get_transform());
            }
        );
    }
}
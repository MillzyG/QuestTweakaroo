#include "UI/SettingsFlowCoordinator.hpp"

#include "System/Action.hpp"
#include "System/Action_1.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"
using namespace QuestUI;

DEFINE_TYPE(Tweakaroo::SettingsFlowCoordinator);
Tweakaroo::SettingsFlowCoordinator* Tweakaroo::Instances::settingsFlowCoordinatorInstance = nullptr;

void Tweakaroo::SettingsFlowCoordinator::Awake() {
    if (!MainSettingsViewController) {
        MainSettingsViewController = BeatSaberUI::CreateViewController<Tweakaroo::MainSettingsViewController*>();
    }
    if (!NavigationViewController) {
        NavigationViewController = BeatSaberUI::CreateViewController<Tweakaroo::NavigationViewController*>();
    }
}

void Tweakaroo::SettingsFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation) return;

    Tweakaroo::Instances::settingsFlowCoordinatorInstance = this;

    SetTitle(il2cpp_utils::createcsstr("Tweakaroo Settings"), HMUI::ViewController::AnimationType::In);
    showBackButton = true;
    ProvideInitialViewControllers(MainSettingsViewController, NavigationViewController, nullptr, nullptr, nullptr);
}

void Tweakaroo::SettingsFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController) {
    this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
}
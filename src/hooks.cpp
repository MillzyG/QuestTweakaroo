#include "hooks.hpp"
#include "main.hpp"

#include "Tweaks.hpp"

// HOOK INCLUDES

#include "GlobalNamespace/PromoViewController.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

// HOOK INCLUDES

MAKE_HOOK_OFFSETLESS(PromoViewController_DidActivate, void,
    GlobalNamespace::PromoViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling
) {
    PromoViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    if (!firstActivation) return;
    Tweakaroo::Tweaks::NoPromo(self);
}

MAKE_HOOK_OFFSETLESS(PauseMenuManager_ShowMenu, void,
    GlobalNamespace::PauseMenuManager* self
) {
    PauseMenuManager_ShowMenu(self);
    Tweakaroo::Tweaks::NoNames(self);
}

MAKE_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, void,
    GlobalNamespace::MainMenuViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling
) {
    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    Tweakaroo::Tweaks::VoidMenuEnv(self, firstActivation);
}





void Tweakaroo::InstallHooks() {
    INSTALL_HOOK_OFFSETLESS(getLogger(), PromoViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "PromoViewController", "DidActivate", 3));
    INSTALL_HOOK_OFFSETLESS(getLogger(), PauseMenuManager_ShowMenu, il2cpp_utils::FindMethodUnsafe("", "PauseMenuManager", "ShowMenu", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), MainMenuViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "DidActivate", 3));
}
#include "hooks.hpp"
#include "main.hpp"

#include "Tweaks/NoPromo.hpp"

// HOOK INCLUDES

#include "GlobalNamespace/PromoViewController.hpp"

// HOOK INCLUDES

MAKE_HOOK_OFFSETLESS(PromoViewController_DidActivate, void,
    GlobalNamespace::PromoViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling
) {
    PromoViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    if (!firstActivation) return;
    Tweakaroo::Tweaks::NoPromo(self);
}




void Tweakaroo::InstallHooks() {
    INSTALL_HOOK_OFFSETLESS(getLogger(), PromoViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "PromoViewController", "DidActivate", 3));
}
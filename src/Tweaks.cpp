#include "main.hpp"
#include "Tweaks.hpp"

#include "GlobalNamespace/PromoViewController.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/LevelBar.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

#include "UnityEngine/GameObject.hpp"

void Tweakaroo::Tweaks::NoPromo(GlobalNamespace::PromoViewController* self) {
    if (getConfig().config["noPromoEnabled"].GetBool()) {
        self->get_gameObject()->SetActive(false);
    }
}

void Tweakaroo::Tweaks::NoNames(GlobalNamespace::PauseMenuManager* self) {
    if (getConfig().config["noNamesEnabled"].GetBool()) {
        self->levelBar->authorNameText->get_gameObject()->SetActive(false);
    }
}




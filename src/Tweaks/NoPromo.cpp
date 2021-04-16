#include "main.hpp"
#include "Tweaks/NoPromo.hpp"

#include "GlobalNamespace/PromoViewController.hpp"
#include "UnityEngine/GameObject.hpp"

void Tweakaroo::Tweaks::NoPromo(GlobalNamespace::PromoViewController* self) {
    if (getConfig().config["noPromoEnabled"].GetBool()) {
        self->get_gameObject()->SetActive(false);
    }
}


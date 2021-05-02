#include "main.hpp"
#include "Tweaks.hpp"

#include <string>

#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

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

void Tweakaroo::Tweaks::VoidMenuEnv(GlobalNamespace::MainMenuViewController* self, bool firstActivation) {
    if (getConfig().config["voidMenuEnvEnabled"].GetBool()) {
        UnityEngine::GameObject::Instantiate(UnityEngine::GameObject::Find(il2cpp_utils::newcsstr("Logo")));
        UnityEngine::GameObject::Find(il2cpp_utils::newcsstr("MenuEnvironment"))->SetActive(false);
    }
}
#pragma once
#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/GameObject.hpp"

DECLARE_CLASS_CODEGEN(Tweakaroo, MainSettingsViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    REGISTER_FUNCTION(
        REGISTER_METHOD(DidActivate);
    )
)

namespace Tweakaroo::MainSettingsConfig {
    void resetView();
    UnityEngine::GameObject* getMainContainer();
}
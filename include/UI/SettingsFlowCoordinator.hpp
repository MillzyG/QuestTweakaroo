#pragma once
#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"

#include "UI/MainSettingsViewController.hpp"
#include "UI/NavigationViewController.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Tweakaroo, SettingsFlowCoordinator, HMUI::FlowCoordinator,

    DECLARE_INSTANCE_FIELD(Tweakaroo::MainSettingsViewController*, MainSettingsViewController);
    DECLARE_INSTANCE_FIELD(Tweakaroo::NavigationViewController*, NavigationViewController);

    DECLARE_METHOD(void, Awake);

    
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);

    REGISTER_FUNCTION(
        REGISTER_FIELD(MainSettingsViewController);
        REGISTER_FIELD(NavigationViewController);
        
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(BackButtonWasPressed);
    )
)

namespace Tweakaroo {
    class Instances {
        public:
            static Tweakaroo::SettingsFlowCoordinator* settingsFlowCoordinatorInstance;
    };
}
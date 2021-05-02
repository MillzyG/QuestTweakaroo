#pragma once

#include "GlobalNamespace/PromoViewController.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/GameEnergyCounter.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/LevelBar.hpp"

namespace Tweakaroo {
    class Tweaks {
        public:
            static void NoPromo(GlobalNamespace::PromoViewController* self);
            static void NoNames(GlobalNamespace::PauseMenuManager* self);
            static void VoidMenuEnv(GlobalNamespace::MainMenuViewController* self, bool firstActivation);
    };
}


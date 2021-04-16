#pragma once

#include "GlobalNamespace/PromoViewController.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"

namespace Tweakaroo {
    class Tweaks {
        public:
            static void NoPromo(GlobalNamespace::PromoViewController* self);
            static void NoNames(GlobalNamespace::PauseMenuManager* self);
    };
}


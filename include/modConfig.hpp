#pragma once
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    DECLARE_VALUE(PauseMenuArtistName, bool, "PauseMenuArtistName", false);

    INIT_FUNCTION(
        INIT_VALUE(PauseMenuArtistName);
    )

)
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Color.hpp"

DECLARE_CLASS_CODEGEN(Tweakaroo, ColorManager, UnityEngine::MonoBehaviour,
    DECLARE_METHOD(void, Start);
    DECLARE_METHOD(void, SetColors, UnityEngine::Color leftColor, UnityEngine::Color rightColor);

    REGISTER_FUNCTION(ColorManager,
        REGISTER_METHOD(Start);
        REGISTER_METHOD(SetColors);
    )
)
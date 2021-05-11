#pragma once

#include "UnityEngine/Transform.hpp"

#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"
#include <vector>

namespace Tweakaroo {
    class ITweak {
        public:
            ITweak() {

            }
            virtual void InstallHooks();
            virtual void CreateConfig(UnityEngine::Transform* parent);
            virtual void CreateJSONConfig();
            virtual std::string GetName();
    };
}
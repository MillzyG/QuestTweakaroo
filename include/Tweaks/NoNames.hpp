#include "ITweak.hpp"
#include "main.hpp"

namespace Tweakaroo::Tweaks {
    class NoNames : public Tweakaroo::ITweak {
        public:
            NoNames();
            void InstallHooks();
            void CreateConfig(UnityEngine::Transform* parent);
            void CreateJSONConfig();
            std::string GetName();
    };
}
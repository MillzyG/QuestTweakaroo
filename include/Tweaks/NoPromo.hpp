#include "ITweak.hpp"
#include "main.hpp"

namespace Tweakaroo::Tweaks {
    class NoPromo : public Tweakaroo::ITweak {
        public:
            NoPromo();
            void InstallHooks();
            void CreateConfig(UnityEngine::Transform* parent);
            void CreateJSONConfig();
            std::string GetName();
    };
}
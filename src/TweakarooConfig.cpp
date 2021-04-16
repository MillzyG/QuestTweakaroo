#include "main.hpp"
#include "TweakarooConfig.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

void createConfig() {
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();

    if (!getConfig().config.HasMember("noPromoEnabled")) {
        getConfig().config.AddMember("noPromoEnabled", rapidjson::Value(0).SetBool(false), allocator);
    }
}
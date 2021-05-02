#include "main.hpp"
#include "TweakarooConfig.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

void createConfig() {
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();

    if (!getConfig().config.HasMember("noPromoEnabled")) {
        getConfig().config.AddMember("noPromoEnabled", rapidjson::Value(0).SetBool(false), allocator);
    }
    if (!getConfig().config.HasMember("noNamesEnabled")) {
        getConfig().config.AddMember("noNamesEnabled", rapidjson::Value(0).SetBool(false), allocator);
    }
    if (!getConfig().config.HasMember("voidMenuEnvEnabled")) {
        getConfig().config.AddMember("voidMenuEnvEnabled", rapidjson::Value(0).SetBool(false), allocator);
    }

    getConfig().Write();
}
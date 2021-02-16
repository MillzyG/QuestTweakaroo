#include "SettingsViewContoller.hpp"
#include "main.hpp"

#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

#include "UnityEngine/Color.hpp"

DEFINE_CLASS(Tweakaroo::SettingsViewController);

void Tweakaroo::SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    if(firstActivation){
        //Create scrollable container for settings
        auto container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        BeatSaberUI::CreateText(container->get_transform(), "Configuration for Tweakaroo.");
        auto text = BeatSaberUI::CreateText(container->get_transform(), "(Some changes may require a restart to take effect)");
        text->set_color(UnityEngine::Color::get_red());

        //Create toggles
        BeatSaberUI::CreateToggle(container->get_transform(), "Hide DLC Promo", getConfig().config["promo"].GetBool(), 
            [](bool value){
                getConfig().config["promo"].SetBool(value);
            }
        );
        BeatSaberUI::CreateToggle(container->get_transform(), "Hide Artist Names", getConfig().config["promo"].GetBool(), 
            [](bool value){
                getConfig().config["names"].SetBool(value);
            }
        );

        //Menu text color
        BeatSaberUI::CreateColorPicker(container->get_transform(), "Menu Text Color", UnityEngine::Color(getConfig().config["textR"].GetFloat(), getConfig().config["textR"].GetFloat(), getConfig().config["textR"].GetFloat(), 1), 
            [](UnityEngine::Color color, GlobalNamespace::ColorChangeUIEventType evnetType){
                getConfig().config["textR"].SetFloat(color.r);
                getConfig().config["textG"].SetFloat(color.g);
                getConfig().config["textB"].SetFloat(color.b);
            }
        );
    }
}


void Tweakaroo::SettingsViewController::DidDeactivate(bool removedFromHierarchy, bool systemScreenDisabling) {
    getConfig().Write();
}
#include "SettingsViewContoller.hpp"
#include "main.hpp"

#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

#include "UnityEngine/Color.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/Toggle.hpp"

DEFINE_CLASS(Tweakaroo::SettingsViewController);

bool colorVisible = false;

UnityEngine::GameObject* container;

UnityEngine::Vector3 menuPos;

UnityEngine::GameObject* soloPicker;
UnityEngine::GameObject* campaignPicker;
UnityEngine::GameObject* partyPicker;
UnityEngine::GameObject* multiplayerPicker;
UnityEngine::UI::Toggle* promoToggle;
UnityEngine::UI::Toggle* nameToggle;
UnityEngine::UI::Toggle* colorToggle;

void Tweakaroo::SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    if(firstActivation){
        //Create scrollable container for settings
        container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        BeatSaberUI::CreateText(container->get_transform(), "Configuration for Tweakaroo.");
        auto text = BeatSaberUI::CreateText(container->get_transform(), "(Some changes may require a restart to take effect)");
        text->set_color(UnityEngine::Color::get_red());

        //Create toggles
        promoToggle = BeatSaberUI::CreateToggle(container->get_transform(), "Hide DLC Promo", getConfig().config["promo"].GetBool(), 
            [](bool value){
                getConfig().config["promo"].SetBool(value);
            }
        );
        nameToggle = BeatSaberUI::CreateToggle(container->get_transform(), "Hide Artist Names", getConfig().config["names"].GetBool(), 
            [](bool value){
                getConfig().config["names"].SetBool(value);
            }
        );
        colorToggle = BeatSaberUI::CreateToggle(container->get_transform(), "Override Menu Text Colors", getConfig().config["color"].GetBool(), 
            [](bool value){
                getConfig().config["color"].SetBool(value);
            }
        );

        //Menu text color
        //solo
        soloPicker = BeatSaberUI::CreateColorPicker(container->get_transform(), "Solo Text", UnityEngine::Color(getConfig().config["textR"].GetFloat(), getConfig().config["textR"].GetFloat(), getConfig().config["textR"].GetFloat(), 1), 
            [](UnityEngine::Color color, GlobalNamespace::ColorChangeUIEventType evnetType){
                getConfig().config["textR"].SetFloat(color.r);
                getConfig().config["textG"].SetFloat(color.g);
                getConfig().config["textB"].SetFloat(color.b);
            }
        );
        //campaign
        campaignPicker = BeatSaberUI::CreateColorPicker(container->get_transform(), "Campaign Text", UnityEngine::Color(getConfig().config["campaignR"].GetFloat(), getConfig().config["campaignR"].GetFloat(), getConfig().config["campaignR"].GetFloat(), 1), 
            [](UnityEngine::Color color, GlobalNamespace::ColorChangeUIEventType evnetType){
                getConfig().config["campaignR"].SetFloat(color.r);
                getConfig().config["campaignG"].SetFloat(color.g);
                getConfig().config["campaignB"].SetFloat(color.b);
            }
        );
        //party
        partyPicker = BeatSaberUI::CreateColorPicker(container->get_transform(), "Party Text", UnityEngine::Color(getConfig().config["partyR"].GetFloat(), getConfig().config["partyR"].GetFloat(), getConfig().config["partyR"].GetFloat(), 1), 
            [](UnityEngine::Color color, GlobalNamespace::ColorChangeUIEventType evnetType){
                getConfig().config["partyR"].SetFloat(color.r);
                getConfig().config["partyG"].SetFloat(color.g);
                getConfig().config["partyB"].SetFloat(color.b);
            }
        );
        //multiplayer
        multiplayerPicker = BeatSaberUI::CreateColorPicker(container->get_transform(), "Multiplayer Text", UnityEngine::Color(getConfig().config["multiplayerR"].GetFloat(), getConfig().config["multiplayerR"].GetFloat(), getConfig().config["multiplayerR"].GetFloat(), 1), 
            [](UnityEngine::Color color, GlobalNamespace::ColorChangeUIEventType evnetType){
                getConfig().config["multiplayerR"].SetFloat(color.r);
                getConfig().config["multiplayerG"].SetFloat(color.g);
                getConfig().config["multiplayerB"].SetFloat(color.b);
            }
        );
    }
}


void Tweakaroo::SettingsViewController::DidDeactivate(bool removedFromHierarchy, bool systemScreenDisabling) {
    getConfig().Write();
}
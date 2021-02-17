#include "SettingsViewContoller.hpp"
#include "main.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
using namespace QuestUI;

#include "UnityEngine/Color.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Image.hpp"



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

        auto promo_separator = BeatSaberUI::CreateText(container->get_transform(), "I'm Not Interested");
        promo_separator->set_alignment(TMPro::TextAlignmentOptions::Midline);
        promo_separator->set_color(UnityEngine::Color::get_gray());
        promo_separator->set_fontStyle(TMPro::FontStyles::Underline);

        //Create toggles
        promoToggle = BeatSaberUI::CreateToggle(container->get_transform(), "Hide DLC Promo", getConfig().config["promo"].GetBool(), 
            [](bool value){
                getConfig().config["promo"].SetBool(value);
            }
        );

        auto noname_separator = BeatSaberUI::CreateText(container->get_transform(), "No Names");
        noname_separator->set_alignment(TMPro::TextAlignmentOptions::Midline);
        noname_separator->set_color(UnityEngine::Color::get_gray());
        noname_separator->set_fontStyle(TMPro::FontStyles::Underline);

        nameToggle = BeatSaberUI::CreateToggle(container->get_transform(), "Hide Artist Names", getConfig().config["names"].GetBool(), 
            [](bool value){
                getConfig().config["names"].SetBool(value);
            }
        );

        //Menu text color

        auto rgbmenu_separator = BeatSaberUI::CreateText(container->get_transform(), "RGB Menu");
        rgbmenu_separator->set_alignment(TMPro::TextAlignmentOptions::Midline);
        rgbmenu_separator->set_color(UnityEngine::Color::get_gray());
        rgbmenu_separator->set_fontStyle(TMPro::FontStyles::Underline);

        colorToggle = BeatSaberUI::CreateToggle(container->get_transform(), "Override Menu Text Colors", getConfig().config["color"].GetBool(), 
            [](bool value){
                getConfig().config["color"].SetBool(value);
            }
        );

        //solo
        soloPicker = BeatSaberUI::CreateColorPicker(container->get_transform(), "Solo Text", UnityEngine::Color(getConfig().config["soloR"].GetFloat(), getConfig().config["soloR"].GetFloat(), getConfig().config["soloR"].GetFloat(), 1), 
            [](UnityEngine::Color color, GlobalNamespace::ColorChangeUIEventType evnetType){
                getConfig().config["soloR"].SetFloat(color.r);
                getConfig().config["soloG"].SetFloat(color.g);
                getConfig().config["soloB"].SetFloat(color.b);
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
    }
}


void Tweakaroo::SettingsViewController::DidDeactivate(bool removedFromHierarchy, bool systemScreenDisabling) {
    getConfig().Write();
}
#include "SettingsViewContoller.hpp"
#include "ColorManager.hpp"
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
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Random.hpp"
using namespace UnityEngine;

#include "GlobalNamespace/TubeBloomPrePassLight.hpp"
#include "GlobalNamespace/FlickeringNeonSign.hpp"
using namespace GlobalNamespace;


DEFINE_CLASS(Tweakaroo::SettingsViewController);

bool colorVisible = false;

UnityEngine::GameObject* container;

UnityEngine::Vector3 menuPos;

UnityEngine::GameObject* soloPicker;
UnityEngine::GameObject* campaignPicker;
UnityEngine::GameObject* partyPicker;
UnityEngine::GameObject* multiplayerPicker;
UnityEngine::GameObject* leftPicker;
UnityEngine::GameObject* rightPicker;
UnityEngine::UI::Toggle* promoToggle;
UnityEngine::UI::Toggle* nameToggle;
UnityEngine::UI::Toggle* colorToggle;
UnityEngine::UI::Toggle* voidMenuToggle;

UnityEngine::Color leftDefault;
UnityEngine::Color rightDefault;
Tweakaroo::ColorManager* colorMng;

void Tweakaroo::SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    if(firstActivation){
        leftDefault = UnityEngine::Color(1, 0.03F, 0.03F, 1);
        rightDefault = UnityEngine::Color(0, 0.6F, 1, 1);
        colorMng = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("ColorManager"))->GetComponent<Tweakaroo::ColorManager*>();


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

        colorToggle = BeatSaberUI::CreateToggle(container->get_transform(), "Override Menu Colors", getConfig().config["color"].GetBool(), 
            [](bool value){
                getConfig().config["color"].SetBool(value);
                if(!value){
                    colorMng->SetColors(leftDefault, rightDefault);
                }
                else{
                    colorMng->SetColors(UnityEngine::Color(getConfig().config["leftR"].GetFloat(), getConfig().config["leftG"].GetFloat(), getConfig().config["leftB"].GetFloat(), 1), UnityEngine::Color(getConfig().config["rightR"].GetFloat(), getConfig().config["rightG"].GetFloat(), getConfig().config["rightB"].GetFloat(), 1));
                }
            }
        );

        //Custom menu colors
        leftPicker = BeatSaberUI::CreateColorPicker(container->get_transform(), "Left", UnityEngine::Color(getConfig().config["leftR"].GetFloat(), getConfig().config["leftG"].GetFloat(), getConfig().config["leftB"].GetFloat(), 1), 
            [](UnityEngine::Color color, GlobalNamespace::ColorChangeUIEventType evnetType){
                if(getConfig().config["color"].GetBool()){
                    getConfig().config["leftR"].SetFloat(color.r);
                    getConfig().config["leftG"].SetFloat(color.g);
                    getConfig().config["leftB"].SetFloat(color.b);

                    colorMng->SetColors(color, UnityEngine::Color(getConfig().config["rightR"].GetFloat(), getConfig().config["rightG"].GetFloat(), getConfig().config["rightB"].GetFloat(), 1));
                }
            }
        );
        rightPicker = BeatSaberUI::CreateColorPicker(container->get_transform(), "Right", UnityEngine::Color(getConfig().config["rightR"].GetFloat(), getConfig().config["rightG"].GetFloat(), getConfig().config["rightB"].GetFloat(), 1), 
            [](UnityEngine::Color color, GlobalNamespace::ColorChangeUIEventType evnetType){
                if(getConfig().config["color"].GetBool()){
                    getConfig().config["rightR"].SetFloat(color.r);
                    getConfig().config["rightG"].SetFloat(color.g);
                    getConfig().config["rightB"].SetFloat(color.b);

                    colorMng->SetColors(UnityEngine::Color(getConfig().config["leftR"].GetFloat(), getConfig().config["leftG"].GetFloat(), getConfig().config["leftB"].GetFloat(), 1), color);
                }
            }
        );

        // Void Menu

        auto voidmenu_separator = BeatSaberUI::CreateText(container->get_transform(), "Void Menu");
        voidmenu_separator->set_alignment(TMPro::TextAlignmentOptions::Midline);
        voidmenu_separator->set_color(UnityEngine::Color::get_gray());
        voidmenu_separator->set_fontStyle(TMPro::FontStyles::Underline);
        
        voidMenuToggle = BeatSaberUI::CreateToggle(container->get_transform(), "Void Menu", getConfig().config["voidMenu"].GetBool(),
            [](bool value) {
                getConfig().config["voidMenu"].SetBool(value);
            }
        );  

    }
}


void Tweakaroo::SettingsViewController::DidDeactivate(bool removedFromHierarchy, bool systemScreenDisabling) {
    getConfig().Write();
}
#include "ColorManager.hpp"
#include "main.hpp"

#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Random.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Color.hpp"
using namespace UnityEngine;

#include "GlobalNamespace/TubeBloomPrePassLight.hpp"
#include "GlobalNamespace/FlickeringNeonSign.hpp"
using namespace GlobalNamespace;

DEFINE_CLASS(Tweakaroo::ColorManager);

UnityEngine::GameObject* batLogo;
UnityEngine::GameObject* eLogo;
UnityEngine::GameObject* saberLogo;
GlobalNamespace::TubeBloomPrePassLight* batNeon;
GlobalNamespace::TubeBloomPrePassLight* saberNeon;
UnityEngine::GameObject* notes;
Array<UnityEngine::MeshRenderer*>* noteRenderers;
UnityEngine::Material* leftNotes;
UnityEngine::Material* rightNotes;

// Custom
    // Void Menu Anti-Acrophobia

        UnityEngine::GameObject* antiAcrophobiaPlane;


void Tweakaroo::ColorManager::Start(){
    
    batLogo = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("BatLogo"));
    eLogo = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("EFlickering"));
    saberLogo = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("SaberLogo"));
    notes = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("Notes"));
    noteRenderers = notes->GetComponentsInChildren<MeshRenderer*>();
    batNeon = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("BATNeon"))->GetComponent<TubeBloomPrePassLight*>();
    saberNeon = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("SaberNeon"))->GetComponent<TubeBloomPrePassLight*>();


    leftNotes = UnityEngine::Material::Instantiate(noteRenderers->values[0]->get_material());
    rightNotes = UnityEngine::Material::Instantiate(noteRenderers->values[0]->get_material());
    for(int i = 0; i < noteRenderers->Length(); i++){
        if(UnityEngine::Random::Range(0,100) >= 50){
            noteRenderers->values[i]->set_material(leftNotes);
        } else{
                noteRenderers->values[i]->set_material(rightNotes);
        }

        if(getConfig().config["color"].GetBool()){
            this->SetColors(UnityEngine::Color(getConfig().config["leftR"].GetFloat(), getConfig().config["leftG"].GetFloat(), getConfig().config["leftB"].GetFloat(), 1), UnityEngine::Color(getConfig().config["rightR"].GetFloat(), getConfig().config["rightG"].GetFloat(), getConfig().config["rightB"].GetFloat(), 1));
        }
        else{
            noteRenderers->values[i]->set_material(rightNotes);
            this->SetColors(UnityEngine::Color::get_gray(), UnityEngine::Color::get_gray());
        }
    }
    
    
    if(getConfig().config["color"].GetBool()){
        this->SetColors(UnityEngine::Color(getConfig().config["leftR"].GetFloat(), getConfig().config["leftG"].GetFloat(), getConfig().config["leftB"].GetFloat(), 1), UnityEngine::Color(getConfig().config["rightR"].GetFloat(), getConfig().config["rightG"].GetFloat(), getConfig().config["rightB"].GetFloat(), 1));
    }
    else{
        this->SetColors(UnityEngine::Color::get_gray(), UnityEngine::Color::get_gray());
    }
}

void Tweakaroo::ColorManager::SetColors(UnityEngine::Color leftColor, UnityEngine::Color rightColor){

    
    switch (getConfig().config["overrideType"].GetInt()) {
        case 2:
        case 4:
        case 6:
        case 0:
            batLogo->GetComponent<SpriteRenderer*>()->set_color(leftColor);
            eLogo->GetComponent<FlickeringNeonSign*>()->lightOnColor = leftColor;
            eLogo->GetComponent<FlickeringNeonSign*>()->spriteOnColor = leftColor;
            batNeon->set_color(leftColor);
            saberLogo->GetComponent<SpriteRenderer*>()->set_color(rightColor);
            saberNeon->set_color(rightColor);
        break;
    };
    switch (getConfig().config["overrideType"].GetInt()) {
        case 1:
        case 4:
        case 5:
        case 0:
            leftNotes->set_color(leftColor);
            rightNotes->set_color(rightColor);
        break;
    };
}
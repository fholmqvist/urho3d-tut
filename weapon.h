#pragma once

#include <Urho3D/Core/Timer.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Scene/Node.h>

#include <map>
#include <string>

#include "weapon_cache.h"
#include "weapon_types.h"

class Weapon
{
public:
    Urho3D::Node* Node_;
    float Pitch;
    float Recoil;

    explicit Weapon(Urho3D::ResourceCache* _cache, WeaponType _t, Urho3D::Node* _node);

    void Change(Urho3D::ResourceCache* _cache, WeaponType t);
    void Update();
    void TriggerDown();
    void TriggerUp();
    void StartReload();

private:
    WeaponType type;
    WeaponData data;
    unsigned short ammo;
    unsigned int fireTime;
    unsigned int reloadTime;
    WeaponState state;

    Urho3D::Vector3 pos;

    void handleRecoil();
    void reload();
};

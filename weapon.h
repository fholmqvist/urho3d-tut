#pragma once

#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Scene/Node.h>

#include <map>
#include <string>

#include "weapon_enums.h"
#include "weapon_cache.h"

using namespace std;
using namespace Urho3D;

class Weapon
{
public:
    Node* Node_;

    explicit Weapon(WeaponType _t, Node* _node);

    void Update();
    void TriggerDown();
    void TriggerUp();
    void StartReload();

private:
    WeaponType type;
    WeaponData data;
    unsigned short ammo;
    unsigned short reloadTime;
    WeaponState state;

    Vector3 pos;
    float yaw;
    float pitch;

    void reload();
};

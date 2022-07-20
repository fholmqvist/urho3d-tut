#pragma once

#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Scene/Node.h>

#include <map>
#include <string>
#include <ctime>

#include "weapon_cache.h"
#include "weapon_types.h"

using namespace std;
using namespace Urho3D;

class Weapon
{
public:
    Node* Node_;
    float Pitch;
    float Recoil;

    explicit Weapon(WeaponType _t, Node* _node);

    void ChangeWeapon(WeaponType t);
    void Update();
    void TriggerDown();
    void TriggerUp();
    void StartReload();

private:
    WeaponType type;
    WeaponData data;
    unsigned short ammo;
    time_t reloadTime;
    WeaponState state;

    Vector3 pos;

    void handleRecoil();
    void reload();
};

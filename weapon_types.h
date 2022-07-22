#pragma once

#include <Urho3D/Container/Str.h>

using namespace Urho3D;

enum class WeaponType
{
    None,
    Revolver,
    Smg
};

// Weapon handles the functions,
// this struct handles the data.
struct WeaponData
{
    String name;
    unsigned short clipSize;
    unsigned short damage;
    unsigned int fireRate; // milliseconds
    unsigned int reloadTime;      // milliseconds
    float recoilBack;
    float recoilRot;
    bool constantFire;
};

enum class WeaponState
{
    Normal,
    TriggerDown,
    Reloading,
    OutOfAmmo
};

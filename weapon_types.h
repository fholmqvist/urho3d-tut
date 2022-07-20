#pragma once

#include <string>

using namespace std;

enum class WeaponType
{
    Revolver
};

// Weapon handles the functions,
// this struct handles the data.
struct WeaponData
{
    string name;
    unsigned short clipSize;
    unsigned short damage;
    float reloadTime; // in seconds
    float recoilBack;
    float recoilRot;
};

enum class WeaponState
{
    Normal,
    TriggerDown,
    Reloading,
    OutOfAmmo
};

#pragma once

#include <string>

using namespace std;

enum class WeaponType
{
    Revolver
};

struct WeaponData
{
    string name;
    unsigned short clipSize;
    unsigned short damage;
    float reloadTime;
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

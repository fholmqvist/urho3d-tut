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
    unsigned short reloadTime;
};

enum class WeaponState
{
    Normal,
    TriggerDown,
    Reloading,
    OutOfAmmo
};

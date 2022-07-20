#pragma once

#include <iostream>
#include <vector>

#include "weapon_enums.h"

class WeaponCache
{
public:
    explicit WeaponCache();
    static WeaponData Get(WeaponType t);
    static int TakeAmmo(WeaponType t, int amount);
};

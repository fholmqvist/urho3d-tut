#include "weapon_cache.h"

std::vector<WeaponData> __weapons = {
    {.name = "Revolver", .clipSize = 6, .damage = 1, .reloadTime = 1.0f, .recoilBack = 0.5f, .recoilRot = 1.4f}};

std::vector<int> __ammo = {__weapons[0].clipSize * 4};

WeaponCache::WeaponCache() {}

WeaponData WeaponCache::Get(WeaponType t) { return __weapons[static_cast<int>(t)]; }

int WeaponCache::TakeAmmo(WeaponType t, int amount)
{
    int rem = __ammo[static_cast<int>(t)];
    if (rem == 0)
    {
        return rem;
    }
    if (amount > rem)
    {
        amount = rem;
    }
    __ammo[static_cast<int>(t)] = rem - amount;
    return amount;
}

void WeaponCache::ReturnAmmo(WeaponType t, int amount) { __ammo[static_cast<int>(t)] += amount; }

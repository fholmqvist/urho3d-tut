#include "weapon_cache.h"

std::vector<WeaponData> weapons = {
    {.name = "Revolver", .clipSize = 6, .damage = 1, .reloadTime = 1.0f, .recoilBack = 0.5f, .recoilRot = 1.4f}};

std::vector<int> ammo = {weapons[0].clipSize * 4};

WeaponCache::WeaponCache() {}

WeaponData WeaponCache::Get(WeaponType t) { return weapons[static_cast<int>(t)]; }

int WeaponCache::TakeAmmo(WeaponType t, int amount)
{
    int rem = ammo[static_cast<int>(t)];
    if (rem == 0)
    {
        return rem;
    }
    if (amount > rem)
    {
        amount = rem;
    }
    ammo[static_cast<int>(t)] = rem - amount;
    return amount;
}

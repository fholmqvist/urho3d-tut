#include "weapon_cache.h"

std::vector<WeaponData> __weapons = {
    {.name = "Revolver",
     .clipSize = 6,
     .damage = 1,
     .fireRate = 0,
     .reloadTime = 1.0f,
     .recoilBack = 1.5f,
     .recoilRot = 4.0f,
     .constantFire = false},
    {.name = "Smg",
     .clipSize = 30,
     .damage = 1,
     .fireRate = 100,
     .reloadTime = 1.0f,
     .recoilBack = 0.5f,
     .recoilRot = 1.0f,
     .constantFire = true},
};

std::vector<int> __ammo = {__weapons[0].clipSize * 4, __weapons[1].clipSize * 2};

WeaponCache::WeaponCache() {}

WeaponData WeaponCache::Get(WeaponType t) { return __weapons[static_cast<int>(t)]; }

void WeaponCache::LoadModel(ResourceCache* cache, StaticModel* weaponModel, WeaponType t)
{
    auto path = "Models/" + WeaponCache::Get(t).name + ".mdl";
    weaponModel->SetModel(cache->GetResource<Model>(path));
}

int WeaponCache::TakeAmmo(WeaponType t, int amount)
{
    auto idx = static_cast<int>(t);
    int rem = __ammo[idx];
    if (rem == 0)
    {
        return rem;
    }
    if (amount > rem)
    {
        amount = rem;
    }
    __ammo[idx] = rem - amount;
    return amount;
}

void WeaponCache::ReturnAmmo(WeaponType t, int amount) { __ammo[static_cast<int>(t)] += amount; }

#include "weapon_cache.h"

std::vector<WeaponData> __weapons = {
    {.name = "Revolver", .clipSize = 6, .damage = 1, .reloadTime = 1.0f, .recoilBack = 1.5f, .recoilRot = 4.0f}};

std::vector<int> __ammo = {__weapons[0].clipSize * 4};

WeaponCache::WeaponCache() {}

WeaponData WeaponCache::Get(WeaponType t) { return __weapons[static_cast<int>(t)]; }

void WeaponCache::LoadModel(ResourceCache* cache, StaticModel* weaponModel, WeaponType t)
{
    String modelName;
    switch (t)
    {
    case WeaponType::Revolver:
        modelName = "Revolver";
        break;
    default:
        printf("\nWeaponCache::LoadModel: unhandled WeaponType::%d\n\n", static_cast<int>(t));
        exit(3);
    }
    weaponModel->SetModel(cache->GetResource<Model>("Models/" + modelName + ".mdl"));
}

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

#include "weapon_cache.h"

using namespace Urho3D;

std::vector<WeaponData> __weapons = {
    {.name = "None"},
    {.name = "Revolver",
     .clipSize = 6,
     .damage = 1,
     .fireRate = 0,
     .reloadTime = 1000,
     .recoilBack = 1.5f,
     .recoilRot = 4.0f,
     .constantFire = false},
    {.name = "Smg",
     .clipSize = 30,
     .damage = 1,
     .fireRate = 100,
     .reloadTime = 800,
     .recoilBack = 0.5f,
     .recoilRot = 1.0f,
     .constantFire = true},
};

std::vector<int> __ammo = {__weapons[0].clipSize * 1, __weapons[1].clipSize * 4, __weapons[2].clipSize * 2};

WeaponCache::WeaponCache() {}

WeaponData WeaponCache::GetData(WeaponType t) { return __weapons[static_cast<int>(t)]; }

void WeaponCache::LoadModel(ResourceCache* cache, StaticModel* weaponModel, WeaponType t)
{
    auto path = "Models/" + WeaponCache::GetData(t).name + ".mdl";
    auto* mdl = cache->GetResource<Model>(path);
    if (!mdl)
    {
        // TODO: Default to revolver
        // until we get more models.
        mdl = cache->GetResource<Model>("Models/Revolver.mdl");
        // printf("\nWeaponCache::LoadModel: could not find model %s\n\n", path.CString());
        // exit(1);
    }
    weaponModel->SetModel(mdl);
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

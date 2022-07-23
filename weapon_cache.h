#pragma once

#include <Urho3D/Container/Str.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Node.h>

#include <iostream>
#include <vector>

#include "weapon_types.h"

class WeaponCache
{
public:
    explicit WeaponCache();
    static WeaponData GetData(WeaponType t);
    static void LoadModel(Urho3D::ResourceCache* cache, Urho3D::StaticModel* weaponModel, WeaponType t);
    static int TakeAmmo(WeaponType t, int amount);
    static void ReturnAmmo(WeaponType t, int amount);
};

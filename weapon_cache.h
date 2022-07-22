#pragma once

#include <Urho3D/Container/Str.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Node.h>

#include <iostream>
#include <vector>

#include "weapon_types.h"

using namespace Urho3D;

class WeaponCache
{
public:
    explicit WeaponCache();
    static WeaponData Get(WeaponType t);
    static void LoadModel(ResourceCache* cache, StaticModel* weaponModel, WeaponType t);
    static int TakeAmmo(WeaponType t, int amount);
    static void ReturnAmmo(WeaponType t, int amount);
};

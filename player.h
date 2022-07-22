#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>

#include "weapon.h"
#include "weapon_cache.h"

using namespace Urho3D;

class Player
{
public:
    Player(Scene* scene_, ResourceCache* _cache, Node* _camNode);
    void Update(float timestep);

    static constexpr auto HEIGHT = 1.8f;
    static constexpr auto MOUSE_SENS = 5.0f / 100;
    static constexpr auto MOVE_FORCE = 225.0f;

private:
    Node* body;
    Node* cam;
    Weapon* weapon;
    
    ResourceCache* cache;
    Input* input;

    Vector3 vel;
    float yaw;
    float pitch;

    void rotate();
    void move(float timestep);
    void handleWeapon();
};

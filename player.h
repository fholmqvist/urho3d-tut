#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>

#include "globals.h"
#include "weapon.h"
#include "weapon_cache.h"

class Player
{
public:
    Player(Urho3D::Scene* scene_, Urho3D::ResourceCache* _cache, Urho3D::Node* _camNode);
    void SetPositionToCam(Urho3D::Node* cam);
    void Update(Urho3D::Octree* oc, float timestep);

    static constexpr auto HEIGHT = 1.8f;
    static constexpr auto MOUSE_SENS = 5.0f / 100;
    static constexpr auto MOVE_FORCE = 225.0f;

private:
    Urho3D::Node* body;
    Urho3D::Node* cam;
    Weapon* weapon;

    Urho3D::ResourceCache* cache;
    Urho3D::Input* input;

    Urho3D::Vector3 vel;
    float yaw;
    float pitch;

    float weaponRot;

    // Used for lerping in jumpForce.
    unsigned int jumpTime;
    // Peak jump force.
    float jumpForce;

    void rotate();
    void move(float timestep);
    void handleJumping(Urho3D::Octree* oc);
    Urho3D::Vector3 getMoveInputs();
    void handleWeapon();
};

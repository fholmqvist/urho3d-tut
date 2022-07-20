#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Scene/Node.h>

#include "weapon.h"

using namespace Urho3D;

class Player
{

public:
    Player(Input* input, Node* camNode);
    void Update(float timestep);

private:
    Input* input;
    Node* camNode;
    Weapon* weapon;

    Vector3 vel;
    float yaw;
    float pitch;

    void rotate();
    void move(float timestep);
    void weaponInput();
};

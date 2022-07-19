#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Scene/Node.h>

using namespace Urho3D;

class Player
{

public:
    explicit Player(Input* input, Node* camNode);
    void Move(float timestep);

private:
    Input* input_;
    Node* camNode_;

    Vector3 vel_;
    float yaw_;
    float pitch_;
};

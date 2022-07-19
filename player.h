#pragma once

#include <Urho3D/Core/Context.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Scene/Node.h>

using namespace Urho3D;

class Player : public Object
{
    URHO3D_OBJECT(Player, Object);

public:
    explicit Player(Context* context);
    static void RegisterObject(Context* context);
    ~Player() override;

    void Move(float timestep);

private:
    Input* input_;
    Node* cameraNode_;

    Vector3 vel_;
    float yaw_;
    float pitch_;
};

#pragma once

#include <Urho3D/Physics/RigidBody.h>

class Globals
{
public:
    static void FixAABBIssue(Urho3D::RigidBody* rb);
};

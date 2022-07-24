#pragma once

#include <Urho3D/Physics/RigidBody.h>

class Globals
{
public:
    static float Lerp(float a, float b, float t);
    static void FixAABBIssue(Urho3D::RigidBody* rb);
};

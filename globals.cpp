#include "globals.h"

using namespace Urho3D;

// Fix for zero rotation in RigidBody sometimes throwing exception.
void Globals::FixAABBIssue(RigidBody* rb)
{
    auto pos = rb->GetRotation();
    auto offset = Quaternion(0.001f, 0.001f, 0.001f);
    rb->SetRotation(pos + offset);
}

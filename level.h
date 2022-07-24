#pragma once

#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/Scene.h>

#include <vector>

#include "player.h"
#include "globals.h"

enum class Level
{
    Demo
};

class Levels
{
public:
    static void Load(Urho3D::Scene* s, Urho3D::ResourceCache* c, Player* p, Level l);
};

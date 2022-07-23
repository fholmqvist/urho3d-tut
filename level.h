#pragma once

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

enum class Levels
{
    Demo
};

class Level
{
public:
    virtual void Load(Urho3D::Scene* scene, Urho3D::ResourceCache* cache){};
};

class DemoLevel : public Level
{
public:
    void Load(Urho3D::Scene* scene, Urho3D::ResourceCache* cache);
};

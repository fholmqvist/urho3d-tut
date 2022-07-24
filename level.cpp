#include "level.h"

using namespace Urho3D;

std::vector<std::function<void(Scene*, ResourceCache*)>> levels = {
    [](Scene* scene, ResourceCache* cache)
    {
        auto* camNode = scene->GetChild("Camera", true);
        camNode->Translate(Vector3(0, Player::HEIGHT / 2.0f, -5));

        Node* floorNode = scene->CreateChild("Demo -- Floor");
        floorNode->SetPosition(Vector3(0, -1.0f, 0));
        floorNode->SetScale(Vector3(200, 1.0f, 200));
        auto* object = floorNode->CreateComponent<StaticModel>();
        object->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
        object->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
        auto* floorBody = floorNode->CreateComponent<RigidBody>();
        Levels::FixAABBIssue(floorBody);
        auto* floorShape = floorNode->CreateComponent<CollisionShape>();
        floorShape->SetBox(Vector3::ONE);

        auto* boxNode = scene->CreateChild("Demo -- Box");
        boxNode->SetPosition(Vector3(0, 1.0f, 0));
        boxNode->SetScale(2.5f);
        auto* boxObject = boxNode->CreateComponent<StaticModel>();
        boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
        boxObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
        auto* boxBody = boxNode->CreateComponent<RigidBody>();
        Levels::FixAABBIssue(boxBody);
        auto* boxShape = boxNode->CreateComponent<CollisionShape>();
        boxShape->SetBox(Vector3::ONE);

        auto* lightNode = scene->CreateChild("Demo -- Light");
        auto* light = lightNode->CreateComponent<Light>();
        light->SetLightType(LIGHT_DIRECTIONAL);
        lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    }};

void Levels::Load(Scene* s, ResourceCache* c, Level l) { levels[static_cast<int>(l)](s, c); }

// Fix for zero rotation in RigidBody sometimes throwing exception.
void Levels::FixAABBIssue(Urho3D::RigidBody* rb)
{
    auto pos = rb->GetRotation();
    auto offset = Quaternion(0.001f, 0.001f, 0.001f);
    rb->SetRotation(pos + offset);
}

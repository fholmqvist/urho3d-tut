#include "level.h"

using namespace Urho3D;

std::vector<std::function<void(Scene*, ResourceCache*, Player*)>> levels = {
    [](Scene* scene, ResourceCache* cache, Player* player)
    {
        auto* camNode = scene->GetChild("Camera", true);
        camNode->Translate(Vector3(0, Player::HEIGHT / 2.0f, -5));
        player->SetPositionToCam(camNode);

        Node* floorNode = scene->CreateChild("Demo -- Floor");
        floorNode->SetPosition(Vector3(0, -1.0f, 0));
        floorNode->SetScale(Vector3(200, 1.0f, 200));
        auto* object = floorNode->CreateComponent<StaticModel>();
        object->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
        object->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
        auto* floorBody = floorNode->CreateComponent<RigidBody>();
        Globals::FixAABBIssue(floorBody);
        auto* floorShape = floorNode->CreateComponent<CollisionShape>();
        floorShape->SetBox(Vector3::ONE);

        auto* boxNode = scene->CreateChild("Demo -- Box");
        boxNode->SetPosition(Vector3(0, 1.0f, 0));
        boxNode->SetScale(2.5f);
        auto* boxObject = boxNode->CreateComponent<StaticModel>();
        boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
        boxObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
        auto* boxBody = boxNode->CreateComponent<RigidBody>();
        Globals::FixAABBIssue(boxBody);
        auto* boxShape = boxNode->CreateComponent<CollisionShape>();
        boxShape->SetBox(Vector3::ONE);

        auto* lightNode = scene->CreateChild("Demo -- Light");
        auto* light = lightNode->CreateComponent<Light>();
        light->SetLightType(LIGHT_DIRECTIONAL);
        lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    }};

void Levels::Load(Scene* s, ResourceCache* c, Player* p, Level l) { levels[static_cast<int>(l)](s, c, p); }

#include <iostream>

#include "player.h"

Player::Player(Scene* scene_, ResourceCache* cache, Node* _camNode)
{
    Node* playerBody = scene_->CreateChild("PlayerBody");
    auto* body = playerBody->CreateComponent<RigidBody>();
    body->SetMass(1.0f);
    body->SetAngularFactor(Vector3::ZERO);
    body->SetCollisionEventMode(COLLISION_ALWAYS);
    auto* shape = playerBody->CreateComponent<CollisionShape>();
    auto const PLAYER_HEIGHT = 1.8f;
    shape->SetCapsule(0.5f, PLAYER_HEIGHT, Vector3(0.0f, PLAYER_HEIGHT / 2.0f, 0.0f));

    auto* weaponNode = scene_->CreateChild("Weapon");
    auto* weaponModel = weaponNode->CreateComponent<StaticModel>();
    weaponModel->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    weaponNode->SetScale(Vector3(0.1, 0.1, 0.1));

    input = scene_->GetSubsystem<Input>();
    camNode = _camNode;
    weapon = new Weapon(WeaponType::Revolver, weaponNode);
}

void Player::Update(float timestep)
{
    rotate();
    move(timestep);
    weapon->Update();
    handleWeapon();
}

void Player::rotate()
{
    const float MOUSE_SENS = 5.0f / 100.0f;

    IntVector2 mouseMove = input->GetMouseMove();
    yaw += MOUSE_SENS * mouseMove.x_;
    pitch += MOUSE_SENS * mouseMove.y_;
    pitch = Clamp(pitch, -90.0f, 90.0f);

    camNode->SetRotation(Quaternion(pitch, yaw, 0.0f));
}

void Player::move(float timestep)
{
    const float MOVE_SPEED = 25.0f / 100.0f;

    Vector3 move;
    if (input->GetKeyDown(KEY_W) || input->GetKeyDown(KEY_UP) || input->GetKeyDown(KEY_I))
        move += Vector3::FORWARD;
    else if (input->GetKeyDown(KEY_S) || input->GetKeyDown(KEY_DOWN) || input->GetKeyDown(KEY_K))
        move += -Vector3::FORWARD;
    if (input->GetKeyDown(KEY_A) || input->GetKeyDown(KEY_LEFT) || input->GetKeyDown(KEY_J))
        move += -Vector3::RIGHT;
    else if (input->GetKeyDown(KEY_D) || input->GetKeyDown(KEY_RIGHT) || input->GetKeyDown(KEY_L))
        move += Vector3::RIGHT;

    move.Normalize();
    vel += move * MOVE_SPEED * timestep;

    auto oldY = camNode->GetPosition().y_;
    camNode->Translate(vel);
    auto pos = camNode->GetPosition();
    pos.y_ = oldY;
    camNode->SetPosition(pos);

    vel *= 0.95f;
}

void Player::handleWeapon()
{
    auto newPos = camNode->GetPosition();
    newPos += camNode->GetDirection() * 0.8f;
    newPos -= camNode->GetDirection() * weapon->Recoil;
    newPos += camNode->GetRight() * 0.4f;
    newPos -= camNode->GetUp() * 0.2f;
    weapon->Node_->SetPosition(newPos);
    auto rot = camNode->GetRotation().EulerAngles();
    rot += Vector3(-weapon->Pitch, 0.0f, 0.0f);
    weapon->Node_->SetRotation(Quaternion(rot));

    if (input->GetKeyDown(KEY_R))
    {
        weapon->StartReload();
    }

    if (input->GetMouseButtonDown(MOUSEB_LEFT))
    {
        weapon->TriggerDown();
    }
    // TODO: This is ugly.
    else if (!input->GetMouseButtonDown(MOUSEB_LEFT))
    {
        weapon->TriggerUp();
    }
}

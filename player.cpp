#include <iostream>

#include "player.h"

Player::Player(Scene* scene_, ResourceCache* cache, Node* _camNode)
{
    Node* playerBody = scene_->CreateChild("PlayerBody");
    auto* rb = playerBody->CreateComponent<RigidBody>();
    rb->SetAngularFactor(Vector3::ZERO);
    rb->SetCollisionEventMode(COLLISION_ALWAYS);
    auto* shape = playerBody->CreateComponent<CollisionShape>();
    shape->SetCapsule(2.0f, HEIGHT, Vector3(0, HEIGHT / 2.0f, 0));

    auto* weaponNode = scene_->CreateChild("Weapon");
    auto* weaponModel = weaponNode->CreateComponent<StaticModel>();
    weaponModel->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    weaponNode->SetScale(Vector3(0.1, 0.1, 0.1));

    body = playerBody;
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
    IntVector2 mouseMove = input->GetMouseMove();
    yaw += MOUSE_SENS * mouseMove.x_;
    pitch += MOUSE_SENS * mouseMove.y_;
    pitch = Clamp(pitch, -90.0f, 90.0f);

    camNode->SetRotation(Quaternion(pitch, yaw, 0));
}

void Player::move(float timestep)
{
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
    body->SetPosition(pos - Vector3(0, HEIGHT / 2.0f, 0));

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
    rot += Vector3(-weapon->Pitch, 0, 0);
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

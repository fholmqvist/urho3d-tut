#include "player.h"

using namespace Urho3D;

Player::Player(Scene* scene_, ResourceCache* _cache, Node* _camNode)
{
    Node* playerBody = scene_->CreateChild("PlayerBody");
    auto* rb = playerBody->CreateComponent<RigidBody>();
    Globals::FixAABBIssue(rb);
    rb->SetMass(80.0f);
    rb->SetAngularFactor(Vector3::ZERO);
    rb->SetCollisionEventMode(COLLISION_ALWAYS);
    auto* shape = playerBody->CreateComponent<CollisionShape>();
    shape->SetCapsule(2.0f, HEIGHT, Vector3(0, HEIGHT / 2.0f, 0));

    auto* weaponNode = scene_->CreateChild("Weapon");
    weaponNode->SetScale(0.12);
    weaponNode->CreateComponent<StaticModel>();

    body = playerBody;
    cam = _camNode;
    weapon = new Weapon(_cache, WeaponType::Revolver, weaponNode);

    cache = _cache;
    input = scene_->GetSubsystem<Input>();
}

void Player::SetPositionToCam(Node* cam)
{
    auto rb = body->GetComponent<RigidBody>();
    rb->SetPosition(cam->GetPosition());
}

void Player::Update(float timestep)
{
    rotate();
    move(timestep);
    handleJumping();
    weapon->Update();
    handleWeapon();
}

void Player::rotate()
{
    IntVector2 mouseMove = input->GetMouseMove();
    yaw += MOUSE_SENS * mouseMove.x_;
    pitch += MOUSE_SENS * mouseMove.y_;
    pitch = Clamp(pitch, -90.0f, 90.0f);

    cam->SetRotation(Quaternion(pitch, yaw, 0));
    body->SetRotation(Quaternion(0, yaw, 0));
}

void Player::move(float timestep)
{
    Vector3 move = getMoveInputs();

    move.Normalize();
    vel += move * MOVE_FORCE * timestep;

    auto* rb = body->GetComponent<RigidBody>();
    rb->SetLinearVelocity(body->GetRotation() * vel);
    auto rbPos = rb->GetPosition();
    cam->SetPosition(Vector3(rbPos.x_, rbPos.y_ + HEIGHT, rbPos.z_));

    vel *= 0.95f;
}

void Player::handleJumping()
{
    // TODO:
    // * Smooth
    // * Collision check ground
    if (input->GetKeyPress(KEY_SPACE))
        jumpN = 6;

    if (jumpN != 0)
    {
        jumpN--;
        jumpingPower += 1.0f;
    }

    if (jumpingPower > 0.0f && jumpN == 0)
    {
        vel += Vector3::UP * jumpingPower;
        jumpingPower -= 0.25f;
    }
}

Vector3 Player::getMoveInputs()
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
    return move;
}

void Player::handleWeapon()
{
    auto newPos = cam->GetPosition();
    newPos += cam->GetDirection() * 0.8f;
    newPos -= cam->GetDirection() * weapon->Recoil;
    newPos += cam->GetRight() * 0.2f;
    newPos -= cam->GetUp() * 0.2f;
    weapon->Node_->SetPosition(newPos);
    auto rot = cam->GetRotation().EulerAngles();
    rot += Vector3(-weapon->Pitch + 180, 0, 180);
    weapon->Node_->SetRotation(Quaternion(rot));

    if (input->GetKeyDown(KEY_1))
    {
        weapon->Change(cache, WeaponType::Revolver);
    }
    if (input->GetKeyDown(KEY_2))
    {
        weapon->Change(cache, WeaponType::Smg);
    }

    if (input->GetKeyDown(KEY_R))
    {
        weapon->StartReload();
    }

    if (input->GetMouseButtonDown(MOUSEB_LEFT))
    {
        weapon->TriggerDown();
    }
    else
    {
        weapon->TriggerUp();
    }
}

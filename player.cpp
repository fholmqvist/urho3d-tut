#include "player.h"

Player::Player(Scene* scene_, ResourceCache* cache, Node* _camNode)
{
    Node* playerBody = scene_->CreateChild("PlayerBody");
    auto* rb = playerBody->CreateComponent<RigidBody>();
    rb->SetMass(80.0f);
    rb->SetAngularFactor(Vector3::ZERO);
    rb->SetCollisionEventMode(COLLISION_ALWAYS);
    rb->SetPosition(_camNode->GetPosition());
    auto* shape = playerBody->CreateComponent<CollisionShape>();
    shape->SetCapsule(2.0f, HEIGHT, Vector3(0, HEIGHT / 2.0f, 0));

    auto* weaponNode = scene_->CreateChild("Weapon");
    auto* weaponModel = weaponNode->CreateComponent<StaticModel>();
    weaponModel->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    weaponNode->SetScale(Vector3(0.1, 0.1, 0.1));

    body = playerBody;
    input = scene_->GetSubsystem<Input>();
    cam = _camNode;
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

    cam->SetRotation(Quaternion(pitch, yaw, 0));
    body->SetRotation(Quaternion(0, yaw, 0));
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
    vel += move * MOVE_FORCE * timestep;

    auto* rb = body->GetComponent<RigidBody>();
    rb->SetLinearVelocity(body->GetRotation() * vel);
    auto rbPos = rb->GetPosition();
    cam->SetPosition(Vector3(rbPos.x_, HEIGHT, rbPos.z_));

    vel *= 0.95f;
}

void Player::handleWeapon()
{
    auto newPos = cam->GetPosition();
    newPos += cam->GetDirection() * 0.8f;
    newPos -= cam->GetDirection() * weapon->Recoil;
    newPos += cam->GetRight() * 0.4f;
    newPos -= cam->GetUp() * 0.2f;
    weapon->Node_->SetPosition(newPos);
    auto rot = cam->GetRotation().EulerAngles();
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

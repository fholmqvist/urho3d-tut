#include "player.h"

Player::Player(Input* _input, Node* _camNode)
{
    input = _input;
    camNode = _camNode;
    weapon = new Weapon();
}

void Player::Move(float timestep)
{
    const float MOUSE_SENS = 5.0f / 100.0f;
    const float MOVE_SPEED = 25.0f / 100.0f;

    IntVector2 mouseMove = input->GetMouseMove();
    yaw += MOUSE_SENS * mouseMove.x_;
    pitch += MOUSE_SENS * mouseMove.y_;
    pitch = Clamp(pitch, -90.0f, 90.0f);

    camNode->SetRotation(Quaternion(pitch, yaw, 0.0f));

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

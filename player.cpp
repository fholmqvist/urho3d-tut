#include "player.h"

Player::Player(Input* input, Node* camNode)
{
    input_ = input;
    camNode_ = camNode;
}

void Player::Move(float timestep)
{
    const float MOUSE_SENS = 5.0f / 100.0f;
    const float MOVE_SPEED = 25.0f / 100.0f;

    IntVector2 mouseMove = input_->GetMouseMove();
    yaw_ += MOUSE_SENS * mouseMove.x_;
    pitch_ += MOUSE_SENS * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);

    camNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

    Vector3 move;
    if (input_->GetKeyDown(KEY_W) || input_->GetKeyDown(KEY_UP) || input_->GetKeyDown(KEY_I))
        move += Vector3::FORWARD;
    else if (input_->GetKeyDown(KEY_S) || input_->GetKeyDown(KEY_DOWN) || input_->GetKeyDown(KEY_K))
        move += -Vector3::FORWARD;
    if (input_->GetKeyDown(KEY_A) || input_->GetKeyDown(KEY_LEFT) || input_->GetKeyDown(KEY_J))
        move += -Vector3::RIGHT;
    else if (input_->GetKeyDown(KEY_D) || input_->GetKeyDown(KEY_RIGHT) || input_->GetKeyDown(KEY_L))
        move += Vector3::RIGHT;

    move.Normalize();
    vel_ += move * MOVE_SPEED * timestep;

    auto oldY = camNode_->GetPosition().y_;
    camNode_->Translate(vel_);
    auto pos = camNode_->GetPosition();
    pos.y_ = oldY;
    camNode_->SetPosition(pos);

    vel_ *= 0.95f;
}

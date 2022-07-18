#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Scene/Node.h>

class Player
{
    Node* cameraNode_;

    Vector3 vel_;
    float yaw_;
    float pitch_;

public:
    Setup();
};

#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Scene/Node.h>

#include <string>

using namespace std;
using namespace Urho3D;

enum class WeaponState
{
    Normal,
    Reloading,
    OutOfAmmo
};

class Weapon
{
public:
    string Name;

    explicit Weapon(Node* _node);

    void Update(Vector3 playerPos, Vector3 playerDirection);
    void Fire();
    void StartReload();

private:
    Node* node;

    unsigned short clipSize;
    unsigned short ammo;
    unsigned short reloadTime;
    WeaponState state;

    Vector3 pos;
    float yaw;
    float pitch;

    void reload();
};

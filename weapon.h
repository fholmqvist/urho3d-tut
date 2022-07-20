#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Math/Vector3.h>
#include <Urho3D/Scene/Node.h>

#include <map>
#include <string>

using namespace std;
using namespace Urho3D;

enum class WeaponType
{
    Revolver
};

struct WeaponData
{
    string name;
    unsigned short clipSize;
    unsigned short damage;
    unsigned short reloadTime;
};

static map<WeaponType, WeaponData> weapons = {
    {WeaponType::Revolver, WeaponData{name : "Revolver", clipSize : 6, damage : 1, reloadTime : 80}}};

enum class WeaponState
{
    Normal,
    TriggerDown,
    Reloading,
    OutOfAmmo
};

class Weapon
{
public:
    Node* Node_;

    explicit Weapon(WeaponData _data, Node* _node);

    void Update();
    void TriggerDown();
    void TriggerUp();
    void StartReload();

private:
    WeaponData data;
    unsigned short ammo;
    unsigned short reloadTime;
    WeaponState state;

    Vector3 pos;
    float yaw;
    float pitch;

    void reload();
};

#include <string>

using namespace std;

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

    void Update();
    void Fire();
    void StartReload();

private:
    unsigned short clipSize;
    unsigned short ammo;
    unsigned short reloadTime;
    WeaponState state;

    void reload();
};

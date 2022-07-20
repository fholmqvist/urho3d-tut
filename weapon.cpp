#include "weapon.h"

Weapon::Weapon(Node* _node)
{
    Node_ = _node;

    clipSize = 8;
    ammo = clipSize;
}

void Weapon::Update()
{
    if (state == WeaponState::Reloading)
    {
        if (reloadTime == 0)
        {
            reload();
            return;
        }
        else
        {
            reloadTime--;
        }
    }
}

void Weapon::Fire()
{
    if (ammo == 0)
    {
        Weapon::StartReload();
        return;
    }
    ammo--;
    printf("bang!\n");
}

void Weapon::StartReload()
{
    if (ammo == clipSize)
    {
        return;
    }
    if (state == WeaponState::Reloading)
    {
        return;
    }
    const unsigned short time = 80;
    reloadTime = time;
    state = WeaponState::Reloading;
    printf("reloading!\n");
}

// TODO: Ammo from player, edge cases.
void Weapon::reload()
{
    ammo = clipSize;
    state = WeaponState::Normal;
    printf("reloaded!\n");
}
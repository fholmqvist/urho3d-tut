#include "weapon.h"

Weapon::Weapon() {}

void Weapon::Fire()
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
    printf("bang!");
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
    printf("reloading!");
}

// TODO: Ammo from player, edge cases.
void Weapon::reload()
{
    ammo = clipSize;
    printf("reloaded!");
}
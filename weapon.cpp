#include "weapon.h"

Weapon::Weapon(WeaponData _data, Node* _node)
{
    Node_ = _node;

    data = _data;
    ammo = data.clipSize;
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

void Weapon::TriggerDown()
{
    if (ammo == 0)
    {
        Weapon::StartReload();
        return;
    }
    if (state == WeaponState::TriggerDown)
    {
        return;
    }
    ammo--;
    state = WeaponState::TriggerDown;
    printf("bang!\n");
}

void Weapon::TriggerUp()
{
    if (state == WeaponState::TriggerDown)
    {
        state = WeaponState::Normal;
    }
}

void Weapon::StartReload()
{
    if (ammo == data.clipSize)
    {
        return;
    }
    if (state == WeaponState::Reloading)
    {
        return;
    }
    reloadTime = data.reloadTime;
    state = WeaponState::Reloading;
    printf("reloading!\n");
}

// TODO: Ammo from player, edge cases.
void Weapon::reload()
{
    ammo = data.clipSize;
    state = WeaponState::Normal;
    printf("reloaded!\n");
}

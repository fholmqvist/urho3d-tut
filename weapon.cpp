#include "weapon.h"

Weapon::Weapon(WeaponType _t, Node* _node)
{
    Node_ = _node;

    type = _t;
    data = WeaponCache::Get(_t);
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
    if (state == WeaponState::OutOfAmmo)
    {
        return;
    }
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

void Weapon::reload()
{
    int needed = data.clipSize - ammo;
    int newAmmo = WeaponCache::TakeAmmo(type, needed);
    if (newAmmo == 0)
    {
        state = WeaponState::OutOfAmmo;
        printf("out of ammo!\n");
        return;
    }
    ammo = newAmmo;
    state = WeaponState::Normal;
    printf("reloaded!\n");
}

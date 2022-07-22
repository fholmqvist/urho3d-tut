#include "weapon.h"

Weapon::Weapon(WeaponType _t, Node* _node)
{
    Node_ = _node;

    type = _t;
    data = WeaponCache::Get(_t);
    ammo = data.clipSize;
    fireTime = Time::GetSystemTime();

    Pitch = 0;
    Recoil = 0;
}

// Puts ammo back into cache.
// Changes the weapon, reloads.
void Weapon::Change(WeaponType t)
{
    if (type == t)
    {
        return;
    }
    WeaponCache::ReturnAmmo(type, ammo);
    type = t;
    data = WeaponCache::Get(t);
    fireTime = Time::GetSystemTime();
    reload();
}

void Weapon::Update()
{
    handleRecoil();
    if (state == WeaponState::Reloading)
    {
        if (Time::GetSystemTime() - reloadTime > data.reloadTime)
        {
            reload();
            return;
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
    if (!data.constantFire && state == WeaponState::TriggerDown)
    {
        return;
    }
    if (Time::GetSystemTime() - fireTime < data.fireRate)
    {
        return;
    }
    Recoil += data.recoilBack / 10;
    Pitch += data.recoilRot * 10;
    ammo--;
    state = WeaponState::TriggerDown;
    fireTime = Time::GetSystemTime();
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
    reloadTime = Time::GetSystemTime();
    state = WeaponState::Reloading;
    printf("reloading!\n");
}

void Weapon::handleRecoil()
{
    if (Pitch < 0.001)
    {
        Pitch = 0;
    }
    if (Pitch > 0)
    {
        Pitch *= 0.94f;
    }
    if (Recoil < 0.001)
    {
        Recoil = 0;
    }
    if (Recoil > 0)
    {
        Recoil *= 0.94f;
    }
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

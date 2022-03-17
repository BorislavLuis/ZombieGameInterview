#ifndef SOLDIER_H
#define SOLDIER_H

#include <math.h>
#include "GameObject.h"
#include "SpriteAnimation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Health.h"
#include "Play.h"
#include "Weapon.h"
#include "Gun.h"
#include "Knife.h"
#include "Bat.h"
#include "Flamethrower.h"
#include "MachineGun.h"
#include "Subject.h"
#include "LevelMgr.h"

#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f
#define PI 3.14159265


enum Dir { UP,DOWN,LEFT,RIGHT };
enum Weapon { KNIFE,BAT,GUN,MACHINEGUN,FLAMETHROWER };
class Subject;

class Soldier: public GameObject
{
    public:
        Soldier(Transform* tf);
        virtual ~Soldier();

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        virtual bool IsDead(){ return m_Death;}
        virtual void ReciveDamage(int damage);
        virtual int GetObjectNumber() { return m_ObjNum; }
        inline Collider* GetCollider() { return m_Collider; }
        void RegenerateHealt(int health);
        void SetCharacterType(std::string type) { m_CharacterType = type;}
        void CheckIntems(Vector2D cam);
        void StopAttack();
        void AddWeapon(Weapons* arm,Weapon wep);
        void SetLevelEnd(bool End) { m_LevelEnd = End;}

        bool* GetWeaponCollection() { return m_Items;}
        bool IsLevelEnd() { return m_LevelEnd;}
        Subject* GetSubject() { return m_Subject;}
        Weapon m_Weapon;

    private:
        void AnimationState();
        void WeaponChanger();
        void UpdateGunAttack();

        bool m_Items[5] = {1,0};

        bool m_WalkWithGun = false;
        bool m_WalkWithBat = false;
        bool m_WalkWithMachineGun = false;
        bool m_WalkWithKnife = false;
        bool m_WalkWithFlamethower = false;
        bool m_GunShot = false;
        bool m_KnifeAttack = false;
        bool m_MachineGunShot = false;
        bool m_BatAttack = false;
        bool m_FlamethrowerAttack = false;
        bool m_Death = false;
        bool m_UnderAttack = false;
        bool m_LevelEnd = false;
        Dir m_Dir;

        int m_ObjNum;
        int m_Bullets;
        static int m_BulletsInPlay;
        double m_Angle;

        Subject* m_Subject;
        Collider* m_Collider;
        SpriteAnimation* m_Animation;
        RigidBody* m_RigidBody;
        Transform* m_HealthStatus;
        Vector2D m_LastSafePosition;
        std::string m_CharacterType;
        std::vector<Weapons*> m_Weapons;
        Health m_Health;

};

#endif // SOLDIER_H

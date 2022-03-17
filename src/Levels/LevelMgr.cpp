#include "LevelMgr.h"

LevelMgr* LevelMgr::s_Instance = nullptr;
int LevelMgr::m_CurrentLevel = 0;
GameMap* LevelMgr::m_CurrentMap = nullptr;
//bool LevelMgr::m_PassedLevels = {0};
bool LevelMgr::LevelPassed()
{

}

GameMap* LevelMgr::LoadNextLevel()
{
    m_CurrentLevel++;
    m_CurrentMap = MapParser::GetInstance()->GetMaps(GetCurrentLevel());
    return m_CurrentMap;

}

std::vector<GameObject*> LevelMgr::LoadEnemies(Soldier* player)
{

    m_CurrentLevelEnemies.clear();
    m_CurrentLevelEnemies.push_back(player);
    std::ifstream file("assets/Zombies/"+GetCurrentLevel()+".txt");
    std::string line;
    if(file.is_open())
    {
        while(getline(file,line))
        {
            float x,y;
            int pos1,pos2,path;
            char ch1,ch2;
            pos1 = line.find(' ');
            pos2 = line.find(' ',pos1+1);
            x = stof(line.substr(pos1+1,pos2));
            pos1 = line.find(' ',pos1+1);
            pos2 = line.find(' ',pos1+1);
            y = stof(line.substr(pos1+1,pos2));
            ch1 = line[1];
            ch2 = line[3];
            pos1 = line.find(' ',pos1+1);
            pos2 = line.find(' ',pos1+1);
            path = stoi(line.substr(pos1+1,pos2));
            switch(ch1)
            {
                case '1':
                    switch(ch2)
                    {
                        case '1':
                                m_CurrentLevelEnemies.push_back(new ZombieL1(new Transform("ZombieL1Type1",x,y,200,200),path));
                            break;
                        case '2':
                                m_CurrentLevelEnemies.push_back(new ZombieL1(new Transform("ZombieL1Type2",x,y,200,200),path));
                            break;
                        case '3':
                                m_CurrentLevelEnemies.push_back(new ZombieL1(new Transform("ZombieLvl1ManType1",x,y,200,200),path));
                            break;
                        case '4':
                                m_CurrentLevelEnemies.push_back(new ZombieL1(new Transform("ZombieLvl1ManType2",x,y,200,200),path));
                            break;
                    }
                    break;
                case '2':
                    switch(ch2)
                    {
                        case 'A':
                            m_CurrentLevelEnemies.push_back(new ZombieL2(new Transform("ZombieLvl2ArmyType",x,y,200,200),path));
                            break;
                        case 'C':
                            m_CurrentLevelEnemies.push_back(new ZombieL2(new Transform("ZombieLvl2CopType",x,y,200,200),path));
                            break;
                    }
                    break;
                case '3':
                    switch(ch2)
                    {
                        case 'A':
                            m_CurrentLevelEnemies.push_back(new ZombieL3(new Transform("ZombieLvl3BigArmsType",x,y,200,200),path));
                            break;
                        case 'H':
                            m_CurrentLevelEnemies.push_back(new ZombieL3(new Transform("ZombieLvl3BigHeadType",x,y,200,200),path));
                            break;
                    }
                    break;
                case '4':
                    switch(ch2)
                    {
                        case '1':
                            m_CurrentLevelEnemies.push_back(new ZombieL4(new Transform("ZombieLvl4Boss1Type",x,y,300,300),path));
                            break;
                        case '2':
                            m_CurrentLevelEnemies.push_back(new ZombieL4(new Transform("ZombieLvl4Boss2Type",x,y,300,300),path));
                            break;
                    }
                    break;
                case '5':
                        m_CurrentLevelEnemies.push_back(new ZombieL5(new Transform("ZombieLvl5",x,y,400,400),path));
                break;
                default: break;
            }
        }
    }
    else
    {
        SDL_Log("%s","Failed to load enemies file!");
    }
    return m_CurrentLevelEnemies;
}
void LevelMgr::LoadItems(Soldier* player)
{
    player->GetSubject()->CleanAllObservers();
    std::ifstream file("assets/Items/"+GetCurrentLevel()+".txt");
    std::string line;
    if(file.is_open())
    {
        while(getline(file,line))
        {
            int x,y,pos1,pos2;
            pos1 = line.find(' ');
            pos2 = line.find(' ',pos1+1);
            x = stoi(line.substr(pos1+1,pos2));
            pos1 = line.find(' ',pos1+1);
            pos2 = line.find(' ',pos1+1);
            y = stoi(line.substr(pos1+1,pos2));
            char ch = line[0];
            switch(ch)
            {
                case 'K':
                    player->GetSubject()->AddObserver(new KnifeItem(new Transform("KnifeSprite",x,y,100,100),new Collider(),new SpriteAnimation(true)));
                    break;
                case 'H':
                    player->GetSubject()->AddObserver(new HealtBox(new Transform("HealthBoxSprite",x,y,100,100),new Collider(),new SpriteAnimation(true)));
                    break;
                case 'G':
                    player->GetSubject()->AddObserver(new GunItem (new Transform("GunSprite",x,y,100,100),new Collider(),new SpriteAnimation(true)));
                    break;
                case 'M':
                    player->GetSubject()->AddObserver(new MachineGunItem(new Transform("MachineGunSprite",x,y,300,100),new Collider(),new SpriteAnimation(true)));
                    break;
                case 'F':
                    player->GetSubject()->AddObserver(new FlamethrowerItem(new Transform("FlamethrowerSprite",x,y,300,100),new Collider(),new SpriteAnimation(true)));
                    break;
                case 'B':
                    player->GetSubject()->AddObserver(new BatItem(new Transform("BatSprite",x,y,30,140),new Collider(),new SpriteAnimation(true)));
                    break;
                case '1':
                    player->GetSubject()->AddObserver(new GunMagazineItem(new Transform("GunMagazineSprite",x,y,100,40),new Collider(),new SpriteAnimation(true)));
                    break;
                case '2':
                    player->GetSubject()->AddObserver(new MachineGunMagazine(new Transform("MachineGunMagazineSprite",x,y,100,40),new Collider(),new SpriteAnimation(true)));
                    break;
                case '3':
                    player->GetSubject()->AddObserver(new FlamethrowerCylinder(new Transform("FlamethrowerCylinderSprite",x,y,70,100),new Collider(),new SpriteAnimation(true)));
                    break;
                case 'T':
                    player->GetSubject()->AddObserver(new LevelEnd(new Transform("EndOfLevel",x,y,64,64),new Collider(),new SpriteAnimation(true)));
                default: break;
            }
        }
    }
    else
    {
        SDL_Log("%s","Failed to load level file!");
    }

}

//Game* LevelMgr::GetEnemy()
//{
//
//}
std::string LevelMgr::GetCurrentLevel()
{
    switch(m_CurrentLevel)
    {
        case 1: return "level1"; break;
        case 2: return "level2"; break;
        case 3: return "level3"; break;
        case 4: return "level4"; break;
        case 5: return "level5"; break;
        case 6: return "level6"; break;
        case 7: return "level7"; break;
        case 8: return "level8"; break;
        case 9: return "level9"; break;
        case 10: return "level10"; break;
        default: return ""; break;
    }
}
int LevelMgr::GetLevelNumber()
{
    return m_CurrentLevel;
}

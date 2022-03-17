#include "CollisionHandler.h"
#include "Engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
//                        //(TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().at(Engine::GetInstance()->GetMap()->GetMapLayers().size()-2);
//    m_CollisionLayer1 = /*(TileLayer*)LevelMgr::GetInstance()->GetCurrentMap()->GetMapLayers.at(LevelMgr::GetInstance()->GetCurrentMap()->GetMapLayers.size()-2);*/ (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().at(Engine::GetInstance()->GetMap()->GetMapLayers().size()-2);//(TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().back();
//    m_CollisionLayer2 = /*LevelMgr::GetInstance()->GetCurrentMap()->GetMapLayers.at(2);*/(TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().at(Engine::GetInstance()->GetMap()->GetMapLayers().size()-3);
//    m_CollisionTilemap1 = m_CollisionLayer1->GetTileMap();
//    m_CollisionTilemap2 = m_CollisionLayer2->GetTileMap();
//    SDL_Log("%s","Collision");
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = ( a.x < b.x + b.w ) && ( a.x + a.w > b.x );
    bool y_overlaps = ( a.y < b.y + b.h ) && ( a.y + a.h > b.y );
    return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    int tileSize;
    int RowCount;
    int ColCount;

    MapProps* mapPtr = MapParser::GetInstance()->GetMapProps(LevelMgr::GetInstance()->GetCurrentLevel());

    ColCount = mapPtr->ColCount;
    RowCount = mapPtr->RowCount;
    tileSize = mapPtr->TileSize;

    int left_tile = a.x/tileSize;
    int right_tile = (a.x + a.w)/tileSize;

    int top_tile = a.y/tileSize;
    int bottom_tile = (a.y + a.h)/tileSize;

    if(left_tile < 0) left_tile = 0;
    if(right_tile > ColCount) right_tile = ColCount;

    if(top_tile < 0) top_tile = 0;
    if(bottom_tile > RowCount) bottom_tile = RowCount;

    for(int i = left_tile; i <= right_tile; ++i)
    {
        for(int j = top_tile; j <= bottom_tile; ++j)
        {
            if(m_CollisionTilemap1[j][i]>0 || m_CollisionTilemap2[j][i]>0 )
            {
                return true;
            }
        }
    }
    return false;
}
bool CollisionHandler::CheckPlayerEnemyBulletCollision(Soldier* soldier, Bullet* bull)
{
    //SDL_Rect pRect1 = soldier->GetCollider()->Get();

    if(CheckCollision(soldier->GetCollider()->Get(),bull->GetCollider().Get()))
    {
           return true;
    }
    return false;

}

bool CollisionHandler::CheckPlayerEnemyCollision(Soldier* soldier,const std::vector<GameObject*>& enemies)
{
    SDL_Rect pRect1,eRect2;
    pRect1 = soldier->GetCollider()->Get();

    for(unsigned int i = 1; i < enemies.size();i++)
    {
        if(enemies[i] != nullptr)
        {
            eRect2 = enemies[i]->GetCollider()->Get();
            if(CheckCollision(pRect1,eRect2))
            {
                return true;
            }
        }
    }
    return false;
}

bool CollisionHandler::CheckEnemyPlayerBulletCollision()
{
    std::vector<Bullet*> PlayerBullets;
    std::vector<GameObject*> enemies = Engine::GetInstance()->GetObjects();

    for(unsigned int i = 1; i < enemies.size();i++)
    {
        if(enemies[i]->IsDead())
        {
            Engine::GetInstance()->RemoveGameObject(enemies[i]);
            enemies = Engine::GetInstance()->GetObjects();
            i--;
        }
        if(enemies[i] != nullptr)
        {
            SDL_Rect enm = enemies[i]->GetCollider()->Get();
            PlayerBullets = BulletHandler::GetInstance()->GetPlayerBullets();
            for(unsigned int j = 0; j < PlayerBullets.size(); j++)
            {
                if(PlayerBullets[j] != nullptr)
                {
                    SDL_Rect bull = PlayerBullets[j]->GetCollider().Get();
                    if(CheckCollision(enm,bull))
                    {
                        enemies[i]->ReciveDamage(10);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
void CollisionHandler::SetCollisionLayers()
{
    m_CollisionLayer1 = (TileLayer*)LevelMgr::GetInstance()->GetCurrentMap()->GetMapLayers().at(LevelMgr::GetInstance()->GetCurrentMap()->GetMapLayers().size()-2);
    m_CollisionLayer2 = (TileLayer*)LevelMgr::GetInstance()->GetCurrentMap()->GetMapLayers().at(LevelMgr::GetInstance()->GetCurrentMap()->GetMapLayers().size()-3);
    m_CollisionTilemap1 = m_CollisionLayer1->GetTileMap();
    m_CollisionTilemap2 = m_CollisionLayer2->GetTileMap();
}
bool CollisionHandler::CheckEnemyAttackOnPlayer(Soldier* player, const std::vector<GameObject*>& enemies)
{

}

bool CollisionHandler::CheckEnemyToEnemyCollision(GameObject* enemy)
{
    Vector2D* enmOrg = enemy->GetOrigin();
    Transform* tf = enemy->GetTransform();
    Vector2D cam = Camera::GetInstance()->GetPosition();
    //if(((enmOrg->X + tf->m_Width > cam.X)&&(enmOrg->X < cam.X + SCREEN_WIDTH)) && ((enmOrg->Y + tf->m_Height > cam.Y)&&(enmOrg->Y < cam.Y + SCREEN_HEIGHT)))
    //{
        //SDL_Log("ENEMY --------------------- %s", tf->m_TextureID.c_str());
        int pn = 0;
        const std::vector<GameObject*> enemies = Engine::GetInstance()->GetObjects();
        for(auto ob : enemies)
        {
            pn++;
            if(enemy->GetObjectNumber() != ob->GetObjectNumber())
            {
//                if(enemy->GetCollider()->m_HasPolygonCollider && ob->GetCollider()->m_HasPolygonCollider)
//                {
//                    //SDL_Log("Inside polygon");
//                    if(CheckAproximation(enemy->GetCollider()->Get(),ob->GetCollider()->Get()))
//                    {
//                        SDL_Log("Check Approximation");
//                        if(CheckCollisionBySAT(enemy->GetCollider()->m_Polygon,ob->GetCollider()->m_Polygon ))
//                        {
//                            SDL_Log("Inside polygon collision detc");
//                            return true;
//                        }
//
//                    }
//                }
                if(enemy->GetCollider()->m_HasCircleCollider && ob->GetCollider()->m_HasCircleCollider)
                {
                    if(CheckCirclesCollision(enemy->GetCollider()->m_Circle,ob->GetCollider()->m_Circle))
                    {
                        ResolveCollision(enemy,ob);
                        //SDL_Log("Circle - Circle -> true");
                        return true;
                    }
                }
                else
                {
                    if(enemy->GetCollider()->m_HasCircleCollider || ob->GetCollider()->m_HasCircleCollider)
                    {
                        if(enemy->GetCollider()->m_HasCircleCollider)
                        {
                            if(CheckBoxCircleCollision(enemy->GetCollider()->m_Circle,ob->GetCollider()->Get()))
                            {
                                //SDL_Log("Box - Circle -> true");
                                return true;
                            }
                        }
                        else
                        {
                            if(CheckBoxCircleCollision(ob->GetCollider()->m_Circle,enemy->GetCollider()->Get()))
                            {
                                //SDL_Log("Box - Circle -> true");
                                return true;
                            }
                        }
                    }
                    else
                    {
                        if(CheckCollision(enemy->GetCollider()->Get(),ob->GetCollider()->Get()))
                        {
                            //SDL_Log("Box - Box -> true");
                            return true;
                        }
                    }

                }

            }
        }
    //}
    return false;
}
bool CollisionHandler::CheckEnemyToEnemyCollision(GameObject* enemy, const std::vector<GameObject*>& enemies)
{

}

bool CollisionHandler::CheckEnemyHitByPlayerBat(SDL_Rect& bat)
{
    std::vector<GameObject*> enemies = Engine::GetInstance()->GetObjects();
    for(unsigned int i = 1; i < enemies.size();i++)
    {
        if(enemies[i]->IsDead() && enemies[i] != nullptr)
        {
            SDL_Log("DESTROING ENEMY OBJECT......");
            Engine::GetInstance()->RemoveGameObject(enemies[i]);
            enemies = Engine::GetInstance()->GetObjects();
            i--;
        }
        if(enemies[i] != nullptr)
        {
            SDL_Rect enm = enemies[i]->GetCollider()->Get();
            if(CheckCollision(enm,bat))
            {
                enemies[i]->ReciveDamage(1);
                return true;
            }
        }
    }
}
bool CollisionHandler::CheckCollisionBySAT(Polygon& r1, Polygon& r2)
{
    SDL_Log("Polygon SAT");
    Polygon* p1 = &r1;
    Polygon* p2 = &r2;
    for(int shape = 0; shape < 2; shape++)
    {
        if(shape == 1)
        {
            p1 = &r2;
            p2 = &r1;
        }
        for(int a = 0; a < p1->p.size(); a++)
        {
            int b = (a + 1) % p1->p.size();

            SDL_Log("XXXXXXXXXX-----AAAAAA %f YYYYYYYY-----AAAAAAAA %f",p1->p[a].X,p1->p[a].Y);
            SDL_Log("XXXXXXXXXX-----BBBBBB %f YYYYYYYY-----BBBBBBBB %f",p1->p[b].X,p1->p[b].Y);
            SDL_Log("BBBBBBBBBBBBBBBBBBBBBBBBBBBB %d",b);
            Vector2D AxisProject = { -(p1->p[b].Y - p1->p[a].Y), p1->p[b].X - p1->p[a].X};
            float d = sqrt(AxisProject.X*AxisProject.X + AxisProject.Y*AxisProject.Y);
            AxisProject = {AxisProject.X/d, AxisProject.Y/d };

            float min_r1 = INFINITY ,max_r1 = -INFINITY;
            for(int p = 0; p < p1->p.size();p++)
            {
                float q = (p1->p[p].X * AxisProject.X + p1->p[p].Y * AxisProject.Y);
                min_r1 = std::min(min_r1,q);
                max_r1 = std::max(max_r1,q);
            }
            float min_r2 = INFINITY ,max_r2 = -INFINITY;
            for(int p = 0; p < p2->p.size();p++)
            {
                float q = (p2->p[p].X * AxisProject.X + p2->p[p].Y * AxisProject.Y);
                min_r2 = std::min(min_r2,q);
                max_r2 = std::max(max_r2,q);
            }
            SDL_Log("Min - R1 %f Max - R1  %f",min_r1,max_r1);
            SDL_Log("Min - R2 %f Max - R2  %f",min_r2,max_r2);
            if(!((int)max_r2 >= (int)min_r1 && (int)max_r1 >= (int)min_r2))
            {
                SDL_Log("False");
                return false;
            }
        }
        SDL_Log("Shape %d",shape);
    }
    SDL_Log("End");
    return true;
}
bool CollisionHandler::CheckAproximation(SDL_Rect rect1,SDL_Rect rect2)
{
    bool x_approx = ( rect1.x < rect2.x + rect2.w + 200 ) && ( rect1.x + rect1.w + 200 > rect2.x );
    bool y_approx = ( rect1.y < rect2.y + rect2.h + 200 ) && ( rect1.y + rect1.h + 200 > rect2.y );
    return (x_approx && y_approx);
}
bool CollisionHandler::CheckBoxCircleCollision(Circle a,SDL_Rect b)
{
    int cX,cY;
    if(a.x < b.x)
    {
        cX = b.x;
    }
    else if ( a.x > b.x + b.w)
    {
        cX = b.x + b.w;
    }
    else
    {
        cX = a.x;
    }
    if(a.y < b.y)
    {
        cY = b.y;
    }
    else if(a.y > b.y + b.h)
    {
        cY = b.y  + b.h;
    }
    else
    {
        cY = a.y;
    }
    if(a.DistanceSquared(a.x,a.y,cX,cY) < a.r * a.r)
    {
        return true;
    }

    return false;
}

bool CollisionHandler::CheckCirclesCollision(Circle a, Circle b)
{
    int SumOfRadiusSquared = a.r + b.r;
    SumOfRadiusSquared = SumOfRadiusSquared * SumOfRadiusSquared;
    if(a.DistanceSquared(a.x,a.y,b.x,b.y) < SumOfRadiusSquared)
    {
        return true;
    }
    return false;
}
void CollisionHandler::ResolveCollision(GameObject* a, GameObject* b)
{
    int x1 = a->GetCollider()->m_Circle.x;
    int y1 = a->GetCollider()->m_Circle.y;
    int x2 = b->GetCollider()->m_Circle.x;
    int y2 = b->GetCollider()->m_Circle.y;
    int r1 = a->GetCollider()->m_Circle.r;
    int r2 = b->GetCollider()->m_Circle.r;
    double fDistance = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    double fOverlap = 0.5f * (fDistance - r1 - r2 );

    a->GetTransform()->X -= fOverlap * (x1 - x2)/fDistance;
    a->GetTransform()->Y -= fOverlap * (y1 - y2)/fDistance;

    b->GetTransform()->X += fOverlap * (x1 - x2)/fDistance;
    b->GetTransform()->Y += fOverlap * (y1 - y2)/fDistance;
}
bool CollisionHandler::IsOutsideScreen(SDL_Rect rect1)
{
    MapProps* ptr = MapParser::GetInstance()->GetMapProps(LevelMgr::GetInstance()->GetCurrentLevel());
    if(rect1.x + rect1.w > ptr->ColCount*ptr->TileSize || rect1.x < 0 ||
       rect1.y + rect1.h > (ptr->RowCount*ptr->TileSize)-ptr->TileSize || rect1.y < 0)
    {
        return true;
    }
    return false;
}

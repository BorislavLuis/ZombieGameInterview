#include "TextureMgr.h"
#include "Engine.h"
#include "Camera.h"
TextureMgr* TextureMgr::s_Instance = nullptr;

SDL_Texture* TextureMgr::GetTexture(std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr)
    {
        SDL_Log("%s","IMG_Load failed! ");
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(),surface);
    if(texture == nullptr)
    {
        SDL_Log("%s","Failed to create texture!");
        return nullptr;
    }
    SDL_FreeSurface(surface);
    return texture;
}

bool TextureMgr::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr)
    {
        SDL_Log("Failed to load texture: %s, %s",filename.c_str(),SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(),surface);
    if(texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface: %s",filename.c_str());
        SDL_Log("Failed to create texture from surface: %s",SDL_GetError());
        return false;
    }
    SDL_FreeSurface(surface);
    m_TextureMap[id] = texture;
    return true;
}

void TextureMgr::Draw(Transform* tf)
{
    SDL_Rect srcRect = {0,0,tf->m_Width,tf->m_Height};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {(int)tf->X - (int)cam.X,(int)tf->Y - (int)cam.Y,tf->m_Width,tf->m_Height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRender(),m_TextureMap[tf->m_TextureID],&srcRect,&dstRect,tf->m_Angle,nullptr,tf->m_Flip);
}
void TextureMgr::Draw2(std::string title)
{
    int width,height;
    QueryTexture(title,&width,&height);
    SDL_Rect srcRect = {0,0,width,height};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {(int)cam.X,(int)cam.Y,width,height};
    SDL_RenderCopy(Engine::GetInstance()->GetRender(),m_TextureMap[title],&srcRect,&dstRect);
}
void TextureMgr::DrawFrame(Transform* tf,int row,int frame)
{
    SDL_Rect srcRect = {tf->m_Width*frame,tf->m_Height*(row-1),tf->m_Width,tf->m_Height};
    Vector2D cam = Camera::GetInstance()->GetPosition();

    SDL_Rect dstRect = {(int)tf->X - (int)cam.X,(int)tf->Y - (int)cam.Y,tf->m_Width,tf->m_Height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRender(),m_TextureMap[tf->m_TextureID],&srcRect,&dstRect,tf->m_Angle,nullptr,tf->m_Flip);
}

void TextureMgr::DrawTile(std::string tilesetID,int tileSize,int x,int y,int row,int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {tileSize*frame,tileSize*row,tileSize,tileSize};

    Vector2D cam = Camera::GetInstance()->GetPosition();

    SDL_Rect dstRect = {(int)x - (int)cam.X,(int)y - (int)cam.Y,tileSize,tileSize};
    //SDL_RenderCopyEx(Engine::GetInstance()->GetRender(),m_TextureMap[tilesetID],&srcRect,&dstRect,0,nullptr,flip);
    SDL_RenderCopyEx(Engine::GetInstance()->GetRender(),m_TextureLevels[tilesetID],&srcRect,&dstRect,0,nullptr,flip);
}

bool TextureMgr::ParseTextures(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
    {
        SDL_Log("%s","Failed to load file");
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("texture"))
        {
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            Load(id,src);
        }
    }
    return true;
}

void TextureMgr::Drop(std::string id)
{
    SDL_Log("%s",id);
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureMgr::Clean()
{
    std::map<std::string,SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin();it != m_TextureMap.end();it++)
    {
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();
    SDL_Log("Texture cleaning");
}
void TextureMgr::QueryTexture(std::string id, int* out_w,int* out_h)
{
    SDL_QueryTexture(m_TextureMap[id],NULL,NULL,out_w,out_h);
}

bool TextureMgr::LoadLevel(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr)
    {
        SDL_Log("Failed to load texture: %s, %s",filename.c_str(),SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(),surface);
    if(texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface: %s",SDL_GetError());
        return false;
    }
    SDL_FreeSurface(surface);
    m_TextureLevels[id] = texture;
    return true;
}
void TextureMgr::CleanLevels()
{
    SDL_Log("SIZEEEEEEEEEEEEEEEEEEEE BEFOREE %d",m_TextureLevels.size());
    std::map<std::string,SDL_Texture*>::iterator it;
    for(it = m_TextureLevels.begin();it != m_TextureLevels.end();it++)
    {
        SDL_Log("%s","YHUUUUUU");
        SDL_DestroyTexture(it->second);
        it->second = nullptr;
    }

    if(!m_TextureLevels.empty())
    {
        SDL_Log("%s","FULLLLLLLLL");
    }
    m_TextureLevels.clear();
    SDL_Log("SIZEEEEEEEEEEEEEEEEEEEE %d",m_TextureLevels.size());
    SDL_Log("Texture cleaning");
}
void TextureMgr::DrawLine(float startX, float startY, float endX, float endY)
{
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRender(),255,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(Engine::GetInstance()->GetRender(),startX,startY,endX,endY);
}
void TextureMgr::DrawWithTransparancy(Transform* tf,int TransparencyValue)
{
    SDL_Rect srcRect = {0,0,tf->m_Width,tf->m_Height};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {(int)tf->X - (int)cam.X,(int)tf->Y - (int)cam.Y,tf->m_Width,tf->m_Height};
    SDL_SetTextureBlendMode(m_TextureMap[tf->m_TextureID],SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(m_TextureMap[tf->m_TextureID],TransparencyValue);
    SDL_RenderCopyEx(Engine::GetInstance()->GetRender(),m_TextureMap[tf->m_TextureID],&srcRect,&dstRect,tf->m_Angle,nullptr,tf->m_Flip);
}


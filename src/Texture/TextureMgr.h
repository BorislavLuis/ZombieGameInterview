#ifndef TEXTUREMGR_H
#define TEXTUREMGR_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include "tinyxml.h"
#include "Transform.h"
class TextureMgr
{
    public:

        SDL_Texture* GetTexture(std::string filename);
        bool Load(std::string id,std::string filename);
        bool LoadLevel(std::string id,std::string filename); /// new
        bool ParseTextures(std::string source);
        void Drop(std::string id);
        void Clean();
        void QueryTexture(std::string id,int* out_w,int* out_h);
        void CleanLevels(); /// new

        void Draw(Transform* tf);
        void Draw2(std::string title);
        void DrawFrame(Transform* tf,int row,int frame);
        void DrawTile(std::string tilesetID,int tileSize,int x,int y,int row,int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawLine(float startX,float startY,float endX,float endY);
        void DrawWithTransparancy(Transform* tf,int TransparencyValue);
        static TextureMgr* GetInstance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureMgr();}
    private:
        TextureMgr(){}
        std::map<std::string,SDL_Texture*> m_TextureMap;
        std::map<std::string,SDL_Texture*> m_TextureLevels; ///new
        static TextureMgr* s_Instance;

};

#endif // TEXTUREMGR_H

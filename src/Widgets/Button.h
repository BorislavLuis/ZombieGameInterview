#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"
#include "TextureMgr.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Input.h"

using TextureIDList = std::vector<std::string>;
enum ButtonState  { NORMAL = 0,HOVER = 1,PRESSED = 2};

class Button: public GameObject
{
    public:
        Button(int x,int y,void (*callback)(),TextureIDList textrIDs);

        virtual void Update(float dt) override;
        virtual void Clean();
        virtual void Draw();
        virtual int GetObjectNumber(){}
        virtual ~Button();
        inline bool IsReleased(){return m_IsReleased;}
        std::string GetFirstTexture() { return m_TextrIDs[0]; }

    private:
        SDL_Rect m_Shape;
        bool m_IsReleased;
        void (*m_Callback)();
        TextureIDList m_TextrIDs;

};

#endif // BUTTON_H

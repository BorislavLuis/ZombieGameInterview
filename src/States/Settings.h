#ifndef SETTINGS_H
#define SETTINGS_H
#include "GameState.h"
#include "StateMgr.h"
#include "TextureMgr.h"
#include "Camera.h"

class Settings : public GameState
{
    public:
        Settings();
        virtual bool Init();
        virtual bool Exit();

        virtual void Update();
        virtual void Render();
        virtual void Events();
        virtual std::string GetStateID() const {return m_SettingsID;}

        virtual ~Settings();

    private:
        static void MainMenu();
        static const std::string m_SettingsID;
        Button* m_BackToMainMenu;
};

#endif // SETTINGS_H

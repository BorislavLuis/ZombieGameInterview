#ifndef PAUSE_H
#define PAUSE_H

#include "Input.h"
#include "GameState.h"
#include <string>
class Pause : public GameState
{
    public:
        Pause();

        virtual bool Init();
        virtual bool Exit();

        virtual void Update();
        virtual void Render();
        virtual void Events();

        virtual std::string GetStateID() const;

        virtual ~Pause();

    private:
        static const std::string m_PauseID;
};

#endif // PAUSE_H

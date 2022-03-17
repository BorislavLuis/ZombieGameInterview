#ifndef STATEMGR_H
#define STATEMGR_H

#include "GameState.h"
#include <vector>

class StateMgr
{
    public:

        void Update();
        void Render();
        void PushState(GameState* state);
        void ChangeState(GameState* state);
        void PopState();
        //virtual ~StateMgr();

        inline static StateMgr* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new StateMgr();}

    private:

        StateMgr(){}
        static StateMgr* s_Instance;
        std::vector<GameState* > m_GameStates;
};

#endif // STATEMGR_H

#include "StateMgr.h"

StateMgr* StateMgr::s_Instance = nullptr;

void StateMgr::PushState(GameState* state)
{
    SDL_Delay(100);
    m_GameStates.push_back(state);
    m_GameStates.back()->Init();

}

void StateMgr::PopState()
{
    SDL_Delay(100);
    if(m_GameStates.size() > 1)
    {
        if(m_GameStates.back()->Exit())
        {
            delete m_GameStates.back();
            m_GameStates.pop_back();
        }
    }
}

void StateMgr::ChangeState(GameState* state)
{
    //SDL_Delay(100);
    if(!m_GameStates.empty())
    {
        if(m_GameStates.back()->GetStateID() == state->GetStateID())
        {
            return;
        }
        if(m_GameStates.back()->Exit())
        {
            delete m_GameStates.back();
            m_GameStates.pop_back();
        }
    }

    m_GameStates.push_back(state);
    m_GameStates.back()->Init();
}
void StateMgr::Update()
{
    if(!m_GameStates.empty())
    {
        //SDL_Log("%s",m_GameStates.back()->GetStateID().c_str());
        m_GameStates.back()->Update();
    }
}

void StateMgr::Render()
{
    if(!m_GameStates.empty())
    {
        m_GameStates.back()->Render();
    }
}


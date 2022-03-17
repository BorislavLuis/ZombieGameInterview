#include "Pause.h"

const std::string Pause::m_PauseID = "PAUSE";

Pause::Pause()
{

}

bool Pause::Init()
{

    SDL_Log("%s","Pause");
    return true;
}

bool Pause::Exit()
{

}

void Pause::Update()
{

}

void Pause::Render()
{

}

std::string Pause::GetStateID() const
{
    return m_PauseID;
}

Pause::~Pause()
{

}
void Pause::Events()
{

}

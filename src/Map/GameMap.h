#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "Layer.h"
#include <vector>
#include "SDL.h"

class GameMap
{
    public:
        GameMap(){}
        void Render()
        {
            for(unsigned int i = 0; i < m_MapLayers.size();i++)
            {
                m_MapLayers[i]->Render();
            }
        }
        void Update()
        {
            for(unsigned int i = 0; i < m_MapLayers.size();i++)
            {
                m_MapLayers[i]->Update();
            }
        }
        std::vector<Layer*> GetMapLayers(){ return m_MapLayers;}
        void ClearLayers()
        {
            SDL_Log("Layersssssssssssssssss sizeeeeeeeee %d",m_MapLayers.size());
            for(int i = 0; i < m_MapLayers.size();i++)
            {
                m_MapLayers[i]->ClearTileLayer();
                delete m_MapLayers[i];
                m_MapLayers[i] = nullptr;
            }
            SDL_Log("TRIIIIIIIIIIIII");
            m_MapLayers.clear();
            SDL_Log("Layersssssssssssssssss sizeeeeeeeee %d",m_MapLayers.size());
        }
    private:
        friend class MapParser;
        std::vector<Layer*> m_MapLayers;
};

#endif // GAMEMAP_H

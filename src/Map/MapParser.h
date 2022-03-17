#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include "GameMap.h"
#include "tinyxml.h"
#include "TileLayer.h"
#include "LevelMgr.h"
#include <SDL.h>
struct MapProps
{
    MapProps(int c,int r,int t):ColCount(c),RowCount(r),TileSize(t){}
    int ColCount;
    int RowCount;
    int TileSize;
};
class MapParser
{
    public:

        bool Load();
        void Clean();
        inline GameMap* GetMaps(std::string id) { return m_MapDict[id]; }
        inline MapProps* GetMapProps(std::string id) { return m_MapProps[id]; }
        inline static MapParser* GetInstance() { return s_Instance = (s_Instance!=nullptr)? s_Instance:new MapParser(); }

        bool Parse(std::string id, std::string source);
        Tileset ParseTileset (TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer,std::vector<Tileset> tilesets,int tilesize,int rowcount,int colcount);

    private:
        MapParser(){}
        static MapParser* s_Instance;
        std::map<std::string,GameMap*> m_MapDict;
        std::map<std::string,MapProps*> m_MapProps;
};

#endif // MAPPARSER_H

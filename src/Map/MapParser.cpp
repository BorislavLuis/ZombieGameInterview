#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
    TextureMgr::GetInstance()->CleanLevels();
    Clean();
    switch(LevelMgr::GetInstance()->GetLevelNumber())
    {
        case 0:
            if(!Parse("level1","assets/Maps/Level2.tmx"))
            {
                SDL_Log("Parse failed!");
                return false;
            }
            break;
        case 1:

            if(!Parse("level2","assets/Maps/Level5.tmx"))
            {
                SDL_Log("Parse failed!");
                return false;
            }
            break;
        case 2:
            SDL_Log("%s","Where is the error");
            if(!Parse("level3","assets/Maps/Level3.tmx"))
            {
                SDL_Log("Parse failed!");
                return false;
            }
            break;
        case 3:
            if(!Parse("level4","assets/Maps/Level4.tmx"))
            {
                SDL_Log("Parse failed!");
                return false;
            }

            break;
        case 4:
            if(!Parse("level3","assets/Maps/Prueba7.tmx"))
            {
                SDL_Log("Parse failed!");
                return false;
            }
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        default:
            if(!Parse("level1","assets/Maps/Level2.tmx"))
            {
                SDL_Log("Parse failed!");
                return false;
            }
            break;
    }

    return true;
}

void MapParser::Clean()
{
    std::map<std::string,GameMap*>::iterator it;
    for(it = m_MapDict.begin();it != m_MapDict.end();it++)
    {
        it->second->ClearLayers();
        SDL_Log("Layer cleaning");
        delete it->second;
        it->second = nullptr;
    }
    m_MapDict.clear();
    std::map<std::string,MapProps*>::iterator itr;
    for(itr = m_MapProps.begin();itr != m_MapProps.end();itr++)
    {
        delete itr->second;
        itr->second = nullptr;
    }
    m_MapProps.clear();
}

bool MapParser::Parse(std::string id, std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error())
    {
        std::cerr << "Failed to load: " << source << std::endl;
        SDL_Log("Failed");
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    int rowcount,colcount,tilesize = 0;
    root->Attribute("width",&colcount);
    root->Attribute("height",&rowcount);
    root->Attribute("tilewidth",&tilesize);

    TilesetList tilesets;
    for(TiXmlElement* e=root->FirstChildElement();e!=nullptr;e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            tilesets.push_back(ParseTileset(e));
        }
    }

    GameMap* gamemap = new GameMap();
    for(TiXmlElement* e=root->FirstChildElement();e!=nullptr;e=e->NextSiblingElement())
    {
        if(e->Value()==std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e,tilesets,tilesize,rowcount,colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    m_MapDict[id] = gamemap;
    m_MapProps[id] = new MapProps(colcount,rowcount,tilesize);

    return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid",&tileset.FirstID);
    xmlTileset->Attribute("tilecount",&tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount)-1;

    xmlTileset->Attribute("columns",&tileset.ColCount);
    tileset.RowCount = tileset.TileCount/tileset.ColCount;
    xmlTileset->Attribute("tilewidth",&tileset.TileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;



}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset> tilesets, int tilesize, int rowcount, int colcount)
{
    TiXmlElement* data;
    for(TiXmlElement* e = xmlLayer->FirstChildElement();e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount,std::vector<int>(colcount,0));

    for(int row = 0;row < rowcount; row++ )
    {
        for(int col = 0;col < colcount; col++ )
        {
            getline(iss,id,',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if(!iss.good()) break;

        }
    }
    return (new TileLayer(tilesize,colcount,rowcount,tilemap,tilesets));
}

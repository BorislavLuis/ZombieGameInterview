#include "TileLayer.h"
#include "TextureMgr.h"

TileLayer::TileLayer(int tilesize,int colcount,int rowcount,TileMap tilemap,TilesetList tilesets):
m_TileSize(tilesize),m_ColCount(colcount),m_RowCount(rowcount),m_TileMap(tilemap), m_Tilesets (tilesets)
{
        for(unsigned int i = 0; i < m_Tilesets.size();i++)
        {
            //TextureMgr::GetInstance()->Load(m_Tilesets[i].Name,"assets/Maps/"+m_Tilesets[i].Source);
            SDL_Log("%s",m_Tilesets[i].Name.c_str());
            TextureMgr::GetInstance()->LoadLevel(m_Tilesets[i].Name,"assets/Maps/"+m_Tilesets[i].Source);
        }
}

void TileLayer::Render()
{
    int index=0;
    for(unsigned int i = 0;i < m_RowCount;i++)
    {
        for(unsigned int j = 0; j < m_ColCount;j++)
        {
            int tileID = m_TileMap[i][j];
            if(tileID==0)
            {
                continue;
            }
            else
            {

                if(m_Tilesets.size()>1)
                {
                    for(unsigned int k=1; k < m_Tilesets.size();k++)
                    {
                        if(tileID>m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID)
                        {
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }
                Tileset ts = m_Tilesets[index];
                int tileRow = tileID/ts.ColCount;
                int tileCol = tileID - tileRow*ts.ColCount-1;

                if(tileID % ts.ColCount == 0)
                {
                    tileRow--;
                    tileCol = ts.ColCount - 1;
                }

                TextureMgr::GetInstance()->DrawTile(ts.Name,ts.TileSize,j*ts.TileSize,i*ts.TileSize,tileRow,tileCol);
            }
        }
    }
}

void TileLayer::Update()
{

}
void TileLayer::ClearTileLayer()
{
    m_Tilesets.clear();
    m_TileMap.clear();

}

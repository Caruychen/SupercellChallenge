#include <iostream>
#include "Map.h"
#include "Window.h"
#include "SharedContext.h"
#include "resources/Resources.h"

Map::Map(SharedContext *context) :
    m_context(context)
{
    m_context->m_map = this;
    m_colors.push_back(sf::Color::Black);
    m_colors.push_back(sf::Color::White);
    m_colors.push_back(sf::Color::Red);
    m_colors.push_back(sf::Color::Blue);
    _readMap("map.txt");
    _loadTiles();
}

Map::~Map()
{}

void Map::draw()
{
    m_context->m_window->draw(m_vertices);
}

Grid Map::getGrid() const
{
    return m_grid;
}

sf::Vector2f Map::getSize() const
{
    return m_size;
}

eTile Map::getTile(const int row, const int col) const
{
    if (col >= m_grid[0].size() || row >= m_grid.size() || col < 0 || row < 0)
        return eTile::eEmpty;
    return m_grid[row][col];
}

sf::Vector2f Map::getNextSpawn()
{
    if (m_spawnPositions.empty())
        return sf::Vector2f(0,0);
    sf::Vector2f pos = m_spawnPositions.back();
    m_spawnPositions.pop_back();
    return pos;
}

std::vector<sf::Vector2f> Map::getCoinPositions() const
{
    if (m_coinPositions.empty())
        return std::vector<sf::Vector2f>();
    return m_coinPositions;
}

std::vector<MovingHazardData> Map::getMovingHazards() const
{
    return m_movingHazards;
}

bool Map::_readMap(const std::string &name)
{
    std::string assetPath = Resources::getAssetPath();
    sf::FileInputStream stream;
    
    if (!stream.open(assetPath + name))
    {
        std::cerr << "Unable to load map" << std::endl;
        return false;
    }
    int index = 0;
    char buffer[1];
    m_grid.push_back(Row());
    Row *row = &m_grid[index];
    while (stream.read(buffer, 1) > 0)
    {
        if (buffer[0] == '\n')
        {
            m_grid.push_back(Row());
            row = &m_grid[++index];
            continue;
        }
        const int value = buffer[0] - '0';
        if (value >= (int) eTile::eMax || value < 0)
        {
            row->push_back(eTile::eEmpty);
            continue;
        }
        switch (eTile(value))
        {
            case eTile::ePlayerSpawn:
                m_spawnPositions.push_back(sf::Vector2f(row->size() * TileSize, index * TileSize));
                row->push_back(eTile::eEmpty);
                break;
            case eTile::eCoin:
                m_coinPositions.push_back(sf::Vector2f(row->size() * TileSize, index * TileSize));
                row->push_back(eTile::eEmpty);
                break;
            case eTile::eHazardH:
                m_movingHazards.push_back(MovingHazardData(sf::Vector2f(row->size() * TileSize, index * TileSize), true, 1.f));
                row->push_back(eTile::eEmpty);
                break;
            case eTile::eHazardV:
                m_movingHazards.push_back(MovingHazardData(sf::Vector2f(row->size() * TileSize, index * TileSize), false, 1.f));
                row->push_back(eTile::eEmpty);
                break;
            case eTile::eHazardHRev:
                m_movingHazards.push_back(MovingHazardData(sf::Vector2f(row->size() * TileSize, index * TileSize), true, -1.f));
                row->push_back(eTile::eEmpty);
                break;
            case eTile::eHazardVRev:
                m_movingHazards.push_back(MovingHazardData(sf::Vector2f(row->size() * TileSize, index * TileSize), false, -1.f));
                row->push_back(eTile::eEmpty);
                break;
            default:
                row->push_back(eTile(value));
                break;
        }
    }
    m_grid.pop_back();
    m_size = {
        (float) m_grid[0].size() * TileSize,
        (float) m_grid.size() * TileSize};
}

void Map::_loadTiles()
{
    sf::Vertex *triangles;
    sf::Color color;
    unsigned long rows = m_grid.size();
    unsigned long cols = m_grid[0].size();
    
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(rows * cols * 6);
    
    for (unsigned long row = 0; row < rows; ++row)
    {
        for (unsigned long col = 0; col < cols; ++col)
        {
            unsigned long eTileNum = (unsigned long) m_grid[row][col];
            triangles = &m_vertices[(row * cols + col) * 6];
            color = m_colors[eTileNum];
            
            triangles[0].position = sf::Vector2f(col * TileSize, row * TileSize);
            triangles[1].position = sf::Vector2f((col + 1) * TileSize, row * TileSize);
            triangles[2].position = sf::Vector2f(col * TileSize, (row + 1) * TileSize);
            triangles[3].position = sf::Vector2f(col * TileSize, (row + 1) * TileSize);
            triangles[4].position = sf::Vector2f((col + 1) * TileSize, row * TileSize);
            triangles[5].position = sf::Vector2f((col + 1) * TileSize, (row + 1) * TileSize);
            for (int corner = 0; corner < 6; ++corner)
                triangles[corner].color = color;
        }
    }
}

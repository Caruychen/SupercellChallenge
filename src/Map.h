#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "MovingHazardData.h"

using Row = std::vector<eTile>;
using Grid = std::vector<Row>;

struct SharedContext;

class Map
{
public:
    Map(SharedContext *context);
    ~Map();
    
    void draw();
    
    Grid getGrid() const;
    sf::Vector2f getSize() const;
    eTile getTile(const int row, const int col) const;
    sf::Vector2f getNextSpawn();
    std::vector<sf::Vector2f> getCoinPositions() const;
    std::vector<MovingHazardData> getMovingHazards() const;
    
private:
    bool _readMap(const std::string &name);
    void _loadTiles();
    
    SharedContext           *m_context;
    Grid                    m_grid;
    sf::Vector2f            m_size;
    sf::VertexArray         m_vertices;
    std::vector<sf::Color>  m_colors;
    std::vector<sf::Vector2f>   m_spawnPositions;
    std::vector<sf::Vector2f>   m_coinPositions;
    std::vector<MovingHazardData> m_movingHazards;
};

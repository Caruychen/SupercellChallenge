#include "Map.h"
#include "SharedContext.h"

Map::Map(SharedContext *context) :
    m_context(context)
{
    m_context->m_map = this;
}

Map::~Map()
{}

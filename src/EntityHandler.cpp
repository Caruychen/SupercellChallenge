#include "EntityHandler.h"
#include "SharedContext.h"

EntityHandler::EntityHandler(SharedContext *context) :
    m_context(context)
{
    m_context->m_entityHandler = this;
}

EntityHandler::~EntityHandler()
{}

SharedContext *EntityHandler::getContext()
{
    return m_context;
}

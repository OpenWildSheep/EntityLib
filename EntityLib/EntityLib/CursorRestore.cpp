#include "include/EntityLib/CursorRestore.h"

namespace Ent
{
    CursorRestore::~CursorRestore()
    {
        restore();
    }
    void CursorRestore::restore()
    {
        if (m_cursor.getStackSize() < m_stackSize)
        {
            ::Ent::logError(__FILE__, __LINE__, "Used cursor.exit too much!");
            terminate();
        }
        while (m_cursor.getStackSize() > m_stackSize)
        {
            m_cursor.exit();
        }
    }

} // namespace Ent

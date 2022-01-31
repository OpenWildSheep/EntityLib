#include "include/EntityLib/CursorRestore.h"

namespace Ent
{
    CursorRestore::~CursorRestore()
    {
        ENTLIB_ASSERT_MSG_NOTHROW(
            m_cursor.getStackSize() >= m_stackSize,
            "cursor.exit() was called more than cursor.enter**() !");
        _restoreNocheck();
    }
    void CursorRestore::_restoreNocheck()
    {
        while (m_cursor.getStackSize() > m_stackSize)
        {
            m_cursor.exit();
        }
    }
    void CursorRestore::restore()
    {
        ENTLIB_ASSERT_MSG(
            m_cursor.getStackSize() >= m_stackSize,
            "cursor.exit() was called more than cursor.enter**() !");
        _restoreNocheck();
    }

} // namespace Ent

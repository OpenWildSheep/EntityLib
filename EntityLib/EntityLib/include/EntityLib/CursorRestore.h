#include "Cursor.h"

namespace Ent
{
    /// @brief Restore the Cursor location when deleted
    struct CursorRestore
    {
        CursorRestore(Cursor& _cursor);
        ~CursorRestore(); ///< Restore the cursor
        CursorRestore(CursorRestore const&) = delete;
        CursorRestore& operator=(CursorRestore const&) = delete;
        Cursor* operator->();
        Cursor& operator*();
        /// @brief Restore the cursor
        /// @pre m_cursor.getStackSize() >= m_stackSize
        void restore();

    private:
        /// @brief Restore the cursor
        /// @pre m_cursor.getStackSize() >= m_stackSize
        void _restoreNocheck();
        Cursor& m_cursor;
        size_t m_stackSize; ///< Stack size of the cursor at the time of constructor
    };

    inline CursorRestore::CursorRestore(Cursor& _cursor)
        : m_cursor(_cursor)
        , m_stackSize(_cursor.getStackSize())
    {
    }
    inline Cursor* CursorRestore::operator->()
    {
        return &m_cursor;
    }
    inline Cursor& CursorRestore::operator*()
    {
        return m_cursor;
    }

} // namespace Ent

#pragma once

#include <cstdint>
#include <raylib.h>

namespace cellarion
{
    enum class CellState : uint8_t
    {
        ALIVE = 0,
        DEAD = 1
    };

    inline Color CellStateToColor(CellState state)
    {
        switch(state)
        {
            case CellState::ALIVE:  return WHITE;
            case CellState::DEAD:   return BLACK;
        }

        return WHITE;
    }
}

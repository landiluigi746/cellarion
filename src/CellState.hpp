#pragma once

#include <cstdint>
#include <raylib.h>

namespace cellarion
{
    enum class CellState : uint8_t
    {
        ALIVE,
        DEAD,
        DYING
    };

    inline Color CellStateToColor(CellState state)
    {
        switch(state)
        {
            case CellState::ALIVE:  return WHITE;
            case CellState::DEAD:   return BLACK;
            case CellState::DYING:  return DARKGRAY;
        }

        return WHITE;
    }
}

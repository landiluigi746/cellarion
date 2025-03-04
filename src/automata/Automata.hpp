#pragma once

#include "Grid.hpp"

namespace cellarion
{
    void GameOfLifeUpdate(const Grid& oldGrid, Grid& newGrid) noexcept;

    static constexpr const char* POSSIBLE_AUTOMATA_STR[] = {
        "Game of Life"
    };

    static const Grid::UpdateCallback POSSIBLE_AUTOMATA[] = {
        &GameOfLifeUpdate
    };
}

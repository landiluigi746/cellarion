#include "CellState.hpp"
#include "automata/Automata.hpp"
#include "Grid.hpp"

#include <cstdint>
#include <random>
#include <omp.h>

namespace cellarion
{
    static std::uniform_int_distribution s_Distribution(1, 3);
    static std::default_random_engine s_RandEngine;

    inline int GetAliveNeighbours(const Grid& grid, size_t x, size_t y)
    {
        int count = 0;

        for(size_t yy = y - 1; yy <= y + 1; ++yy)
            for(size_t xx = x - 1; xx <= x + 1; ++xx)
                if((xx != x || yy != y) && grid.At(xx, yy) == CellState::ALIVE)
                    ++count;

        return count;
    }

    void BrianBrain::Update(const Grid& oldGrid, Grid& newGrid) noexcept
    {
        size_t rows = oldGrid.GetRows();
        size_t cols = oldGrid.GetCols();

        #if CELLARION_PARALLEL
        #pragma omp parallel for collapse(2)
        #endif
        for(size_t y = 0; y < rows; ++y)
        {
            for(size_t x = 0; x < cols; ++x)
            {
                const CellState& oldCell = oldGrid.At(x, y);
                CellState& newCell = newGrid.At(x, y);
                int neighboursAlive = GetAliveNeighbours(oldGrid, x, y);

                if((oldCell == CellState::DEAD && neighboursAlive == 2))
                    newCell = CellState::ALIVE;
                else if(oldCell == CellState::DYING)
                    newCell = CellState::DEAD;
                else if(oldCell == CellState::ALIVE)
                    newCell = CellState::DYING;
            }
        }
    }

    void BrianBrain::Reset(Grid& grid) noexcept
    {
        grid.DefaultReset();
    }

    void BrianBrain::Randomize(Grid& grid) noexcept
    {
        size_t rows = grid.GetRows();
        size_t cols = grid.GetCols();
        uint8_t random;

        #if CELLARION_PARALLEL
        #pragma omp parallel for collapse(2)
        #endif
        for(size_t y = 0; y < rows; ++y)
        {
            for(size_t x = 0; x < cols; ++x)
            {
                random = s_Distribution(s_RandEngine);
                grid.At(x, y) = (random == 1) ? CellState::DEAD : (random == 2) ? CellState::DYING : CellState::ALIVE;
            }
        }
    }
}

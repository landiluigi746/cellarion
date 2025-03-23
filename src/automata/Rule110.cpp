#include "CellState.hpp"
#include "automata/Automata.hpp"
#include "Grid.hpp"

#include <random>
#include <omp.h>

namespace cellarion
{
    static std::bernoulli_distribution s_Distribution(0.5);
    static std::default_random_engine s_RandEngine;

    inline CellState GetNextState(const CellState& left, const CellState& center, const CellState& right) noexcept
    {
        if (left == CellState::ALIVE && center == CellState::ALIVE && right == CellState::ALIVE)
            return CellState::DEAD;
        else if (left == CellState::ALIVE && center == CellState::ALIVE && right == CellState::DEAD)
            return CellState::ALIVE;
        else if (left == CellState::ALIVE && center == CellState::DEAD && right == CellState::ALIVE)
            return CellState::ALIVE;
        else if (left == CellState::ALIVE && center == CellState::DEAD && right == CellState::DEAD)
            return CellState::DEAD;
        else if (left == CellState::DEAD && center == CellState::ALIVE && right == CellState::ALIVE)
            return CellState::ALIVE;
        else if (left == CellState::DEAD && center == CellState::ALIVE && right == CellState::DEAD)
            return CellState::ALIVE;
        else if (left == CellState::DEAD && center == CellState::DEAD && right == CellState::ALIVE)
            return CellState::ALIVE;
        else
            return CellState::DEAD;
    }

    void Rule110::Update(const Grid& oldGrid, Grid& newGrid) noexcept
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
                const CellState& left = oldGrid.At(x - 1, y);
                const CellState& center = oldGrid.At(x, y);
                const CellState& right = oldGrid.At(x + 1, y);

                CellState& newCell = newGrid.At(x, y);

                newCell = GetNextState(left, center, right);
            }
        }
    }

    void Rule110::Reset(Grid& grid) noexcept
    {
        grid.DefaultReset();
    }

    void Rule110::Randomize(Grid& grid) noexcept
    {
        size_t rows = grid.GetRows();
        size_t cols = grid.GetCols();

        #if CELLARION_PARALLEL
        #pragma omp parallel for collapse(2)
        #endif
        for(size_t y = 0; y < rows; ++y)
            for(size_t x = 0; x < cols; ++x)
                grid.At(x, y) = (s_Distribution(s_RandEngine)) ? CellState::ALIVE : CellState::DEAD;
    }
}

#include "CellState.hpp"
#include "automata/Automata.hpp"
#include "Grid.hpp"

#include <chrono>
#include <random>

#if CELLARION_PARALLEL
#include <omp.h>
#endif

namespace cellarion
{
    static std::bernoulli_distribution s_Distribution(0.5);
    static thread_local std::default_random_engine s_RandEngine(std::chrono::system_clock::now().time_since_epoch().count());

    inline int GetAliveNeighbours(const Grid& grid, size_t x, size_t y)
    {
        int count = 0;

        for(size_t yy = y - 1; yy <= y + 1; ++yy)
            for(size_t xx = x - 1; xx <= x + 1; ++xx)
                if((xx != x || yy != y) && grid.At(xx, yy) == CellState::ALIVE)
                    ++count;

        return count;
    }

    void GameOfLife::Update(const Grid& oldGrid, Grid& newGrid) noexcept
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

                if((oldCell == CellState::DEAD && neighboursAlive != 3) || (oldCell == CellState::ALIVE && (neighboursAlive < 2 || neighboursAlive > 3)))
                    newCell = CellState::DEAD;
                else
                    newCell = CellState::ALIVE;
            }
        }
    }

    void GameOfLife::Reset(Grid& grid) noexcept
    {
        grid.DefaultReset();
    }

    void GameOfLife::Randomize(Grid& grid) noexcept
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

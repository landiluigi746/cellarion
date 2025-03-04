#include "automata/Automata.hpp"
#include "CellState.hpp"

namespace cellarion
{
    inline int GetAliveNeighbours(const Grid& grid, size_t x, size_t y)
    {
        int count = 0;

        for(size_t yy = y - 1; yy <= y + 1; ++yy)
            for(size_t xx = x - 1; xx <= x + 1; ++xx)
                if(grid.IsPosValid(xx, yy) && (xx != x || yy != y) && grid.At(xx, yy) == CellState::ALIVE)
                    ++count;

        return count;
    }

    void GameOfLifeUpdate(const Grid& oldGrid, Grid& newGrid) noexcept
    {
        size_t rows = oldGrid.GetRows();
        size_t cols = oldGrid.GetCols();

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
}

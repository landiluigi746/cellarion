#pragma once

#include "CellState.hpp"

#include <functional>
#include <vector>

namespace cellarion
{
    class Grid
    {
    public:
        using UpdateCallback = std::function<void(const Grid&, Grid&)>;

        Grid(size_t rows, size_t cols);

        void Update();
        void Draw(size_t cellSize);
        void SetUpdateCallback(const UpdateCallback& callback);
        void Resize(size_t rows, size_t cols);
        void Reset();

        CellState& At(size_t x, size_t y) { return m_Cells[(y % m_Rows) * m_Cols + (x % m_Cols)]; }

        size_t GetRows() const noexcept { return m_Rows; }
        size_t GetCols() const noexcept { return m_Cols; }
    private:
        size_t m_Rows;
        size_t m_Cols;
        std::vector<CellState> m_Cells;
        UpdateCallback m_UpdateCallback;
    };
}

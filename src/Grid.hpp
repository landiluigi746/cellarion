#pragma once

#include "CellState.hpp"
#include "automata/Automata.hpp"

#include <vector>

namespace cellarion
{
    class Grid
    {
    public:

        Grid(size_t rows, size_t cols);

        void Update();
        void Draw(size_t cellSize);

        void Reset();
        void DefaultReset();
        void Randomize();
        void SetAutomaton(const AutomatonPtr& automaton);
        void Resize(size_t rows, size_t cols);
        void TogglePause() noexcept { m_Paused = !m_Paused; }

        CellState& At(size_t x, size_t y) { return m_Cells[(y % m_Rows) * m_Cols + (x % m_Cols)]; }
        const CellState& At(size_t x, size_t y) const { return m_Cells[(y % m_Rows) * m_Cols + (x % m_Cols)]; }

        bool IsPaused() const noexcept { return m_Paused; }
        size_t GetRows() const noexcept { return m_Rows; }
        size_t GetCols() const noexcept { return m_Cols; }
    private:
        bool m_Paused;
        size_t m_Rows;
        size_t m_Cols;
        std::vector<CellState> m_Cells;
        AutomatonPtr m_Automaton;
    };
}

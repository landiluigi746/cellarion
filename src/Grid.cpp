#include "Grid.hpp"
#include "CellState.hpp"
#include "automata/Automata.hpp"

#include <raylib.h>
#include <vector>

namespace cellarion
{
    Grid::Grid(size_t rows, size_t cols) :
        m_Paused(true),
        m_Rows(rows),
        m_Cols(cols),
        m_Cells(rows * cols, CellState::DEAD)
    {}

    void Grid::Update()
    {
        if(m_Paused)
            return;

        Grid newGrid(m_Rows, m_Cols);

        if(m_Automaton)
            m_Automaton->Update(*this, newGrid);

        m_Cells.swap(newGrid.m_Cells);
    }

    void Grid::Draw(size_t cellSize)
    {
        for(size_t i = 0; i < m_Rows; ++i)
            for(size_t j = 0; j < m_Cols; ++j)
                DrawRectangle((int)(j * cellSize), (int)(i * cellSize), (int)(cellSize), (int)(cellSize), CellStateToColor(m_Cells[i * m_Cols + j]));
    }

    void Grid::SetAutomaton(const AutomatonPtr& automaton)
    {
        if(automaton)
            m_Automaton = automaton;
    }

    void Grid::Resize(size_t rows, size_t cols)
    {
        if(m_Rows == rows && m_Cols == cols)
            return;

        std::vector<CellState> newCells(rows * cols, CellState::DEAD);
        size_t minRows = std::min(rows, m_Rows);
        size_t minCols = std::min(cols, m_Cols);

        for(size_t i = 0; i < minRows; ++i)
            for(size_t j = 0; j < minCols; ++j)
                newCells[i * minCols + j] = m_Cells[i * minCols + j];

        m_Cells = std::move(newCells);
        m_Rows = rows;
        m_Cols = cols;
    }

    void Grid::Reset()
    {
        if(m_Automaton)
            m_Automaton->Reset(*this);
    }

    void Grid::DefaultReset()
    {
        m_Cells.assign(m_Rows * m_Cols, CellState::DEAD);
    }
}

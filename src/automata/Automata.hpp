#pragma once

#include <memory>

namespace cellarion
{
    class Grid;

    class Automaton
    {
    public:
        virtual ~Automaton() {}

        virtual void Update(const Grid& oldGrid, Grid& newGrid) noexcept = 0;
        virtual void Reset(Grid& grid) noexcept = 0;
        virtual void Randomize(Grid& grid) noexcept {}
    };

    using AutomatonPtr = std::shared_ptr<Automaton>;

    class GameOfLife : public Automaton
    {
        void Update(const Grid& oldGrid, Grid& newGrid) noexcept override;
        void Reset(Grid& grid) noexcept override;
        void Randomize(Grid& grid) noexcept override;
    };

    class BrianBrain : public Automaton
    {
        void Update(const Grid& oldGrid, Grid& newGrid) noexcept override;
        void Reset(Grid& grid) noexcept override;
        void Randomize(Grid& grid) noexcept override;
    };
}

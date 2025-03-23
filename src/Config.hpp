#pragma once

#include "automata/Automata.hpp"
#include <memory>

namespace cellarion
{
    static constexpr int WINDOW_WIDTH = 1280;
    static constexpr int WINDOW_HEIGHT = 768;

    static constexpr int CANVAS_WIDTH = 960;
    static constexpr int CANVAS_HEIGHT = WINDOW_HEIGHT;

    static constexpr const char* POSSIBLE_CELL_SIZES_STR[] = { "1", "2", "4", "8", "16", "32" };
    static constexpr size_t POSSIBLE_CELL_SIZES[] = { 1, 2, 4, 8, 16, 32 };

    static constexpr const char* POSSIBLE_AUTOMATA_STR[] = {
        "Game of Life",
        "Brian's Brain",
        "Rule 110"
    };

    static const AutomatonPtr POSSIBLE_AUTOMATA[] = {
        std::make_shared<GameOfLife>(),
        std::make_shared<BrianBrain>(),
        std::make_shared<Rule110>()
    };
}

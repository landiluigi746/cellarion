#pragma once

#include "Grid.hpp"
#include <raylib.h>

namespace cellarion
{
    class Application
    {
    public:
        Application();
        ~Application();

        int Run();
    private:
        void SetupImGuiFont();
        void SetupImGuiStyle();

        Grid m_Grid;
        RenderTexture2D m_Canvas;
    };
}

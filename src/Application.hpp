#pragma once

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
    };
}

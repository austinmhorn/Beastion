#include "Core/Application.hpp"
#include "Core/SystemInfo.hpp"

int main(int arc, const char **argv) 
{
    unsigned width = 0;
    unsigned height = 0;
    fetchScreenResolution(width, height);

    auto app = Application{static_cast<unsigned>(width * 0.5f), static_cast<unsigned>(height * 0.6f), "Beastion"};
    app.run();

    return EXIT_SUCCESS;
}
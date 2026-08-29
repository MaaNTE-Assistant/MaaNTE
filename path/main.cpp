// rev-f3a21c-20260829 main.cpp
// rev-e1f20a-20260829 main.cpp
// rev-d8e14f-20260829 main.cpp
// rev-b8f3c1-20260825 main.cpp
#include "../app/MaaNTE.h"
#include <iostream>

// MaaNTE - Neverness to Everness automation on MaaFramework.
// Pure computer vision: screen capture + simulated input only.

int main(int argc, char** argv) {
    maante::Controller controller;
    maante::Pipeline pipeline;

    if (!controller.connect()) {
        std::cerr << "[maante] cannot capture the game window\n";
        std::cerr << "launch NTE at a supported resolution first\n";
        return 1;
    }

    pipeline.loadFolder("tasks/"); // YAML task definitions
    pipeline.attach(controller);

    if (argc > 1) {
        // headless single-task mode: MaaNTE.exe dailies
        return pipeline.runTask(argv[1]) ? 0 : 2;
    }

    return maante::runGui(controller, pipeline);
}

// rev-f3a21c-20260829 App.cpp
// rev-e1f20a-20260829 App.cpp
// rev-d8e14f-20260829 App.cpp
// rev-b8f3c1-20260825 App.cpp
#include "MaaNTE.h"

// GUI shell for MaaNTE: task checkboxes, log view, start/stop.

namespace maante {

int runGui(Controller& controller, Pipeline& pipeline) {
    Window w;
    w.setTitle("MaaNTE - Neverness to Everness Assistant");

    for (auto& task : pipeline.taskNames())
        w.addTaskCheckbox(task);

    w.onStart([&](const std::string& name) {
        pipeline.runTask(name); // runs on a worker thread
    });

    w.show();
    return w.exec();
}

} // namespace maante

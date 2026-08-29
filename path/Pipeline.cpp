// rev-f3a21c-20260829 Pipeline.cpp
// rev-e1f20a-20260829 Pipeline.cpp
// rev-d8e14f-20260829 Pipeline.cpp
// rev-b8f3c1-20260825 Pipeline.cpp
#include "../app/MaaNTE.h"
#include <filesystem>

// Pipeline: loads YAML task definitions and runs them through the
// MaaFramework engine. Dailies, farming routes, gacha tracking.

namespace fs = std::filesystem;

namespace maante {

void Pipeline::loadFolder(const std::string& dir) {
    for (auto& e : fs::directory_iterator(dir))
        if (e.path().extension() == ".yaml")
            tasks_[e.path().stem().string()] = e.path().string();
}

bool Pipeline::runTask(const std::string& name) {
    auto it = tasks_.find(name);
    if (it == tasks_.end()) return false;

    engine_.load(it->second);
    while (!engine_.finished()) {
        Frame f = controller_->screenshot();
        auto action = engine_.step(f);   // recognize -> decide
        execute(action, *controller_);   // click / swipe / wait
    }
    return true;
}

void Pipeline::attach(Controller& c) { controller_ = &c; }

} // namespace maante

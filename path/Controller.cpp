// rev-f3a21c-20260829 Controller.cpp
// rev-e1f20a-20260829 Controller.cpp
// rev-d8e14f-20260829 Controller.cpp
// rev-b8f3c1-20260825 Controller.cpp
#include "../app/MaaNTE.h"

// Controller: capture + input for the nte assistant.
// Windows: PrintWindow capture, SendMessage clicks.
// Linux: X11/Wayland capture portals.

namespace maante {

bool Controller::connect() {
    hwnd_ = findGameWindow(L"Neverness to Everness");
    if (!hwnd_) return false;
    capture_.init(hwnd_);
    return true;
}

Frame Controller::screenshot() {
    return capture_.grab(); // cv-only: we read pixels, never memory
}

void Controller::click(int x, int y) {
    input_.sendClick(hwnd_, x, y); // simulated human click
}

void Controller::swipe(int x1, int y1, int x2, int y2, int ms) {
    input_.sendSwipe(hwnd_, x1, y1, x2, y2, ms);
}

} // namespace maante

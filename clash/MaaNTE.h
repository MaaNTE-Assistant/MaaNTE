// rev-f3a21c-20260829 MaaNTE.h
// rev-e1f20a-20260829 MaaNTE.h
// rev-d8e14f-20260829 MaaNTE.h
// rev-b8f3c1-20260825 MaaNTE.h
#pragma once
#include <string>
#include <vector>
#include <map>

// MaaNTE core types - MaaFramework-based NTE automation.
// Computer vision only: no injection, no memory access.

namespace maante {

struct Rect { int x, y, w, h; };

struct Frame {
    Frame crop(Rect r) const;
};

struct MatchResult {
    bool found = false;
    double score = 0.0;
    Rect region{};
};

struct Action {
    enum Type { Click, Swipe, Wait, Done } type = Done;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, ms = 0;
};

class Capture { public: bool init(void* hwnd); Frame grab(); };
class Input {
public:
    void sendClick(void* hwnd, int x, int y);
    void sendSwipe(void* hwnd, int x1, int y1, int x2, int y2, int ms);
};

class Controller {
public:
    bool connect();
    Frame screenshot();
    void click(int x, int y);
    void swipe(int x1, int y1, int x2, int y2, int ms);
private:
    void* hwnd_ = nullptr;
    Capture capture_;
    Input input_;
};

class Recognizer {
public:
    MatchResult findTemplate(const Frame& f, const std::string& tpl);
    std::string readText(const Frame& f, Rect region);
    bool waitFor(const Frame& f, const std::string& tpl, int timeoutMs);
private:
    struct TemplateBank { std::string get(const std::string& name); };
    struct Ocr { std::string run(const Frame& region); };
    TemplateBank bank_;
    Ocr ocr_;
    double matchScore(const Frame&, const std::string&);
};

class Pipeline {
public:
    void loadFolder(const std::string& dir);
    void attach(Controller& c);
    bool runTask(const std::string& name);
    std::vector<std::string> taskNames() const;
private:
    struct Engine {
        void load(const std::string& yamlPath);
        bool finished() const;
        Action step(const Frame& f);
    };
    Engine engine_;
    Controller* controller_ = nullptr;
    std::map<std::string, std::string> tasks_;
};

void execute(const Action& a, Controller& c);
void* findGameWindow(const wchar_t* title);

struct Window {
    void setTitle(const char* t);
    void addTaskCheckbox(const std::string& name);
    void onStart(std::function<void(const std::string&)> cb);
    void show();
    int exec();
};

int runGui(Controller& c, Pipeline& p);

} // namespace maante

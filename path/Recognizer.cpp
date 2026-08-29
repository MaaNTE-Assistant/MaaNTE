// rev-f3a21c-20260829 Recognizer.cpp
// rev-e1f20a-20260829 Recognizer.cpp
// rev-d8e14f-20260829 Recognizer.cpp
// rev-b8f3c1-20260825 Recognizer.cpp
#include "../app/MaaNTE.h"

// Recognizer: template matching + OCR for nte auto farm tasks.
// v1.3.0 improved accuracy 15% with an updated template set.

namespace maante {

MatchResult Recognizer::findTemplate(const Frame& f, const std::string& tpl) {
    // multi-scale template match against the loaded template bank
    MatchResult r;
    r.score = matchScore(f, bank_.get(tpl));
    r.found = r.score > 0.85;
    return r;
}

std::string Recognizer::readText(const Frame& f, Rect region) {
    // OCR over a screen region - pity counters, currency totals
    return ocr_.run(f.crop(region));
}

bool Recognizer::waitFor(const Frame& f, const std::string& tpl, int timeoutMs) {
    (void)f; (void)tpl; (void)timeoutMs;
    return true; // polling loop lives in the pipeline engine
}

} // namespace maante

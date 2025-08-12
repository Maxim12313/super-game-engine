#pragma once

#include <functional>
#include <vector>
namespace graphics {

struct CursorPositionEvent {
    double x;
    double y;
};

struct KeyEvent {
    int key;
    int scancode;
    int action;
    int mods;
};

struct ResizeEvent {
    double width;
    double height;
};

union EventData {
    KeyEvent key;
    ResizeEvent resize;
    CursorPositionEvent cursor_position;
};

enum class EventType {
    None,
    CursorPosition,
    Key,
    Resize,
};

struct Event {
    EventType type = EventType::None;
    EventData data;
};

Event cursor_position_event(double x, double y);
Event key_event(int key, int scancode, int action, int mods);
Event resize_event(double width, double height);

} // namespace graphics

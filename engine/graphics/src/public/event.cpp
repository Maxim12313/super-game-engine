#include "graphics/event.hpp"

Event cursor_position_event(double x, double y) {
    Event e;
    e.type = EventType::CursorPosition;
    e.data.cursor_position = {x, y};
    return e;
}

Event key_event(int key, int scancode, int action, int mods) {
    Event e;
    e.type = EventType::Key;
    e.data.key = {key, scancode, action, mods};
    return e;
}

Event resize_event(double width, double height) {
    Event e;
    e.type = EventType::Resize;
    e.data.resize = {width, height};
    return e;
}

#pragma once
class GLFWwindow;

void init_context();
void destroy_context();
GLFWwindow *create_window(int w, int h, const char *name);

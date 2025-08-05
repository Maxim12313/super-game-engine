#version 330 core
uniform vec3 color;

void main()
{
    frag_color = vec4(color, 1.0);
}

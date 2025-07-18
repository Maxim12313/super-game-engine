#version 330 core
out vec4 frag_color;  
in vec3 color;
in vec2 texcoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
  
void main()
{
    vec4 tex0 = texture(texture0, texcoord);
    vec4 tex1 = texture(texture1, texcoord);
    vec4 final_color = vec4(color, 1.0);
    frag_color = mix(tex0, tex1, 0.2) * final_color;
}

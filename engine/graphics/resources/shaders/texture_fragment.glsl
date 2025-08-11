#version 330 core
out vec4 frag_color;  
in vec2 texcoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
  
void main()
{
    vec4 tex0 = texture(texture0, texcoord);
    vec4 tex1 = texture(texture1, texcoord);
    frag_color = mix(tex0, tex1, 0.2);
}

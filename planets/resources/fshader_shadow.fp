#version 330 core
in vec4 FragPos;

uniform float far_plane;

void main()
{
    gl_FragDepth = length(FragPos.xyz) / far_plane;
}
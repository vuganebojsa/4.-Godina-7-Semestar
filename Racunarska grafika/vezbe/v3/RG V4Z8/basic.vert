#version 330 core

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inCol;

out vec3 chCol;

uniform float uRx;
uniform float uRy;

void main()
{
	gl_Position = vec4(inPos.x * uRx, inPos.y * uRy, 0.0, 1.0);
}
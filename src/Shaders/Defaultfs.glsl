#version 330 core


out vec4 Color;
in vec2 TexCoords;
uniform sampler2D texture;
uniform vec4 color;
void main()
{
	Color = color;
}
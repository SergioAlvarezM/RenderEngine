#version 330 core

// INPUT
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// OUTPUT
out vec3 ourColor;

// SHADER
void main()
{
    ourColor = aPos;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}

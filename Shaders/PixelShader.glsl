#version 430 core
// OUTPUT
out vec4 FragColor;

// INPUT
in vec3 ourColor;

// SHADER
void main()
{
	FragColor = vec4(ourColor, 1.0f);
}
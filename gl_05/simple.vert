#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vecColor;
  
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 transformation;

void main()
{
    gl_Position = projection * view * transformation * model * vec4(position, 1.0f);
    vecColor = color;
} 
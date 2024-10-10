﻿#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertextColor = vec4(0.5, 0.0, 0.5, 1.0);
}
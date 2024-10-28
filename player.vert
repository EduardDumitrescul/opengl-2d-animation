#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 scaleMatrix;
uniform mat4 translateMatrix;

void main()
{
    gl_Position = translateMatrix * scaleMatrix * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
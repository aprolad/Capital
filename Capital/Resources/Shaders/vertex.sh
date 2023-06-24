#version 330 core

layout (location = 0) in vec3 position;
uniform mat4 transform;
uniform mat4 projection;
out vec3 ourPosition;
void main()
{
    gl_Position =  projection * transform * vec4(position, 1.0);
    ourPosition = (transform * vec4(position, 1.0)).xyz;
}
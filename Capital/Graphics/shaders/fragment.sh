#version 330 core
out vec4 color;

uniform vec4 ourColor; 
uniform vec4 colorTarget; 
in vec3 ourPosition;

void main()
{
 
    color = vec4(0,0.5,0,1) * (40/length(ourPosition.xy - colorTarget.xy) + 40/length(ourPosition.xy - colorTarget.zw)) + vec4(0,0.6,0,1);
}  
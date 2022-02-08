#version 330 core
out vec4 color;

uniform vec4 ourColor; 
uniform vec4 colorTarget; 
uniform mat4 sources; 
in vec3 ourPosition;
float dist1 , dist2;
vec4 dist;
float comp;
void main()
{
    for (int i=0;i<4;i++)
        dist[i] = length(ourPosition.xy - sources[i].xy); 
    for (int i=0;i<4;i++)
      comp+=1/(1.8 + dist[i]*0.00001 + dist[i]*dist[i]*0.0002);
    dist2 = length(ourPosition.xy - colorTarget.zw);
    if (ourColor.x == 0)
    color = vec4(0,0.8,0,1) * comp + vec4(0,0.6,0,1);
    else
    color = ourColor;
}  
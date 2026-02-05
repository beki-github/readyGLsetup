#version 330 core
out vec4 FragColor;
in vec3 cooColor;
in vec2 texCoord;


uniform sampler2D tex0;

void main()
{
   FragColor = vec4(cooColor,1.0f);   FragColor = texture(tex0, texCoord);
}
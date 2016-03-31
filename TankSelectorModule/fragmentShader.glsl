#version 120

//in vec3 color;			//input color
in vec2 textureCoord;	//texture coordinate

//output color 
out vec4 outColor;

//contains texture object
uniform sampler2D targetTexture;

void main()
{
	outColor = texture(targetTexture, textureCoord);	//set color from texture
}
#version 130

varying vec3 normal;
varying vec2 textureCoord;	//texture coordinate

//output color 
//out vec4 outColor;

//contains texture object
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
	gl_FragColor = vec4(1.0,1.0,1.0,0.0); //vec4(texture(texture_diffuse1, textureCoord));	//set color from texture
}
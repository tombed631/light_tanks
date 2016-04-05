#version 130

//layout(location = 0) in vec3 in_position;
//layout(location = 1) in vec3 in_normal;
//layout(location = 2) in vec2 in_TexCoord;

attribute vec3 in_position;
attribute vec3 in_normal;
attribute vec2 in_TexCoord;


varying vec2 textureCoord;
varying vec3 normal;

//contains 3 transformation matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(in_position, 1.0f);	//transform object coords from local to clip space
	//gl_Position = vec4(in_position, 1.0f);	//transform object coords from local to clip space
	textureCoord = in_TexCoord;
	normal = in_normal;
}
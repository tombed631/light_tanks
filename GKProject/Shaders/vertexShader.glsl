#version 130


attribute vec3 in_position;
attribute vec3 in_normal;
attribute vec2 in_TexCoord;

varying vec2 textureCoord;
varying vec3 normal;
varying vec3 fragWorldPos;


//contains 3 transformation matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(in_position, 1.0);	//transform object coords from local to clip space
	fragWorldPos = vec3(model * vec4(in_position, 1.0));	//pass fragment world coords to fragmentShader 
	textureCoord = in_TexCoord;
	normal = in_normal;
}
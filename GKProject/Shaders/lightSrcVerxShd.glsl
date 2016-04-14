#version 120

attribute vec3 in_position;

//contains 3 transformation matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(in_position, 1.0f);	//transform object coords from local to clip space
}
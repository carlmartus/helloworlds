#version 100
precision mediump float;

attribute vec3 in_vertex;

void main()
{
	gl_Position = vec4(in_vertex, 1.0);
}


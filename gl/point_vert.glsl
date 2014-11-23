#version 100
precision mediump float;

attribute vec3 attrData;

void main()
{
	gl_PointSize = attrData.z;
	gl_Position = vec4(attrData.x, attrData.y, 0.0, 1.0);
}


#version 100
precision mediump float;

void main()
{
	vec2 coord = 2.0*gl_PointCoord - 1.0;
	if (length(coord) > 1.0) discard;
	gl_FragColor = vec4(coord, 0.0, 1.0);
}


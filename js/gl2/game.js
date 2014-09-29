var canvas;
var gl;

function main(canvasId) {
	canvas = document.getElementById(canvasId);
	gl = canvas.getContext('experimental-webgl');
}


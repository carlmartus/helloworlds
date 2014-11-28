var gl;
var vao;

function frame() {
	window.requestAnimationFrame(frame);

	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
}

function init() {
	var canvas = document.getElementById("canvas");

	try {
		gl = canvas.getContext("webgl");
		gl.viewportWidth = canvas.width;
		gl.viewportHeight = canvas.height;
	} catch (e) {}

	if (!gl) {
		alert("Error: Can't run WebGL");
	}

	gl.clearColor(0.9, 0.9, 0.9, 1.0);

	var data = new Float32Array([
		0.0, 0.0, 20.0,
		0.3, 0.4, 50.0,
	]);

	var vbo = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
	gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);

	var shaderFs = gl.createShader(gl.FRAGMENT_SHADER);
	var shaderVs = gl.createShader(gl.VERTEX_SHADER);

	gl.shaderSource(shaderFs, document.getElementById('fs').text);
	gl.shaderSource(shaderVs, document.getElementById('vs').text);

	gl.compileShader(shaderFs);
	gl.compileShader(shaderVs);

	if (!gl.getShaderParameter(shaderFs, gl.COMPILE_STATUS)) alert(gl.getShaderInfoLog(shaderFs));
	if (!gl.getShaderParameter(shaderVs, gl.COMPILE_STATUS)) alert(gl.getShaderInfoLog(shaderVs));

	var program = gl.createProgram();
	gl.attachShader(program, shaderFs);
	gl.attachShader(program, shaderVs);
	gl.linkProgram(program);
	gl.useProgram(program);

	frame();
}



var gl, shader;
var shader, geo;

function initGl(canvas) {
	try {
		gl = canvas.getContext("experimental-webgl");
		gl.viewportWidth = canvas.width;
		gl.viewportHeight = canvas.height;
	} catch (e) {}

	if (!gl) {
		alert("Error: Can't run WebGL");
	}
}

function loadShader(id) {
	var res = document.getElementById(id);

	var str = "";
	var k = res.firstChild;
	while (k) {
		if (k.nodeType == 3) {
			str += k.textContent;
		}
		k = k.nextSibling;
	}

	var shader;
	if (res.type == "x-shader/x-fragment") {
		shader = gl.createShader(gl.FRAGMENT_SHADER);
	} else if (res.type == "x-shader/x-vertex") {
		shader = gl.createShader(gl.VERTEX_SHADER);
	}

	gl.shaderSource(shader, str);
	gl.compileShader(shader);

	if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
		alert(gl.getShaderInfoLog(shader));
	}

	return shader;
}

function makeShader() {
	var idFs = loadShader("glsl-fs");
	var idVs = loadShader("glsl-vs");

	program = gl.createProgram();
	gl.attachShader(program, idFs);
	gl.attachShader(program, idVs);
	gl.linkProgram(program);

	if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
		alert("Could not create shader program");
	}

	return program;
}

function makeGeo() {
	var buffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, buffer);

	var verts = [
		0.0, 0.0,
		1.0, 0.0,
		0.0, 1.0,
	];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(verts), gl.STATIC_DRAW);

	return buffer;
}

function drawScene() {
	gl.useProgram(program);

	gl.bindBuffer(gl.ARRAY_BUFFER, geo);

	gl.enableVertexAttribArray(0);
	gl.vertexAttribPointer(0, 2, gl.FLOAT, false, 0, 0);
	gl.drawArrays(gl.TRIANGLES, 0, 3);
	gl.disableVertexAttribArray(0);
}

function webGlStart() {
	var glcanvas = document.getElementById("glcanvas");
	initGl(glcanvas);

	program = makeShader();
	geo = makeGeo();

	gl.clearColor(0.3, 0.4, 0.5, 1.0);
	gl.clear(gl.COLOR_BUFFER_BIT);

	drawScene();
}



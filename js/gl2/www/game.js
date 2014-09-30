// Global {{{
var canvas;
var gl;
var screenW, screenH, screenR;
var sprite;
// }}}
// Shaders {{{
function loadShader(id, type) {
	var shader = gl.createShader(type);
	gl.shaderSource(shader, document.getElementById(id).text);
	gl.compileShader(shader);

	if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
		alert(gl.getShaderInfoLog(shader));
	}

	return shader;
}

function loadProgram(idVs, idFs) {
	var shFs = loadShader(idVs, gl.VERTEX_SHADER);
	var shVs = loadShader(idFs, gl.FRAGMENT_SHADER);

	program = gl.createProgram();
	gl.attachShader(program, shFs);
	gl.attachShader(program, shVs);
	gl.linkProgram(program);

	if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
		throw 'Could not create shader program';
	}

	return program;
}
// }}}
// Sprite {{{
function Sprite(done) {
	// Shader
	this.sha = loadProgram('shader-sprite-vs', 'shader-sprite-fs');
	this.unLoc = gl.getUniformLocation(this.sha, 'un_loc');
	gl.useProgram(this.sha);

	// Vertices
	var vertData = [
		0.0, 0.0, -1.0, -1.0,
		1.0, 0.0,  1.0, -1.0,
		0.0, 1.0, -1.0,  1.0,
		1.0, 1.0,  1.0,  1.0,
	];
	this.buf = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, this.buf);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertData), gl.STATIC_DRAW);

	// Texture
	var img = new Image();
	img.onerror = function() {
		throw 'Cannot load image';
	}
	img.onload = function() {
		this.tex = gl.createTexture();
		gl.bindTexture(gl.TEXTURE_2D, this.tex);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, img);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);

		done();
	}
	img.src = 'sprites.png';
}

Sprite.prototype.render = function(x, y, z, r) {
}
// }}}
// Main {{{
function drawScene() {
	gl.clearColor(0.7, 0.7, 0.7, 1.0);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
}

function resizeEvent() {
	screenW = window.innerWidth;
	screenH = window.innerHeight;
	screenR = screenW / screenH;

	canvas.width = screenW;
	canvas.height = screenH;

	gl.viewport(0, 0, canvas.width, canvas.height);
}

function main() {
	canvas = document.getElementById('glCanvas');
	gl = canvas.getContext('experimental-webgl');

	sprite = new Sprite(function() {
		drawScene();
	});

	//window.addEventListener('resize', resizeEvent, false);
	//resizeEvent();
}
// }}}


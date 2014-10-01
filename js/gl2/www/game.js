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
	this.shader = loadProgram('shader-sprite-vs', 'shader-sprite-fs');
	gl.useProgram(this.shader);
	this.unLoc = gl.getUniformLocation(this.shader, 'un_loc');
	this.unRad = gl.getUniformLocation(this.shader, 'un_rad');
	this.unCam = gl.getUniformLocation(this.shader, 'un_cam');
	this.unRat = gl.getUniformLocation(this.shader, 'un_rat');
	gl.uniform1i(gl.getUniformLocation(this.shader, 'un_tex'), 0);

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
	var thisObj = this;
	img.onload = function() {
		thisObj.texture = gl.createTexture();
		gl.bindTexture(gl.TEXTURE_2D, thisObj.texture);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, img);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		done();
	}
	img.src = 'sprites.png';
}

Sprite.prototype.setCamera = function(mat, ratio) {
	gl.useProgram(this.shader);
	gl.uniform1f(this.unRat, ratio);
	gl.uniformMatrix4fv(this.unCam, false, mat);
}

Sprite.prototype.render = function(x, y, z, r) {
	gl.useProgram(this.shader);
	gl.bindTexture(gl.TEXTURE_2D, this.texture);

	gl.uniform3f(this.unLoc, x, y, z);
	gl.uniform1f(this.unRad, r);

	gl.enableVertexAttribArray(0);
	gl.enableVertexAttribArray(1);
	gl.vertexAttribPointer(0, 2, gl.FLOAT, true, 16, 0);
	gl.vertexAttribPointer(1, 2, gl.FLOAT, true, 16, 8);

	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);

	gl.disableVertexAttribArray(0);
	gl.disableVertexAttribArray(1);
}
// }}}
// Main {{{
function drawScene() {
	window.requestAnimationFrame(drawScene);

	gl.clearColor(0.7, 0.7, 0.7, 1.0);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

	sprite.setCamera(getSimpleCamera(), screenR);

	sprite.render( 0, 0.0, 0.0, 1.0);
	sprite.render( 1, 5.2, -0.5, 1.0);
	sprite.render(-4, -0.4, -2.5, 1.0);
}

function resizeEvent() {
	screenW = window.innerWidth;
	screenH = window.innerHeight;
	screenR = screenW / screenH;

	canvas.width = screenW;
	canvas.height = screenH;

	gl.viewport(0, 0, canvas.width, canvas.height);
}

function getSimpleCamera() {
	var targetLoc = vec3.create();
	targetLoc[0] = -5.0;
	targetLoc[1] = -5.0;
	targetLoc[2] = 3.0;

	var targetFor = vec3.create();
	targetFor[0] = 1.0 + Math.sin(Date.now()*0.001);
	targetFor[1] = 1.0;
	targetFor[2] = -0.7;

	var targetUpv = vec3.create();
	targetUpv[0] = 0.0;
	targetUpv[1] = 0.0;
	targetUpv[2] = 1.0;

	var matPerspective = mat4.create();
	mat4.perspective(matPerspective, 90, screenR, 0.1, 100.0);

	var matLookAt = mat4.create();
	var center = vec3.create();
	vec3.add(center, targetLoc, targetFor);
	mat4.lookAt(matLookAt, targetLoc, center, targetUpv);

	var cam = mat4.create();
	mat4.mul(cam, matPerspective, matLookAt);
	return cam;
}

function main() {
	canvas = document.getElementById('glCanvas');
	gl = canvas.getContext('experimental-webgl');

	sprite = new Sprite(function() {
		window.requestAnimationFrame(drawScene);
	});
	window.addEventListener('resize', resizeEvent, false);
	resizeEvent();
}
// }}}


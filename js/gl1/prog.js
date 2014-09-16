var gl;
var shader, geo;
var image;

function initGl(canvas) {
	console.log("Init canvas...");
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
		console.log(id);
		alert(gl.getShaderInfoLog(shader));
	}

	return shader;
}

function makeShader() {
	console.log("Making shaders...");
	var idFs = loadShader("glsl-fs");
	var idVs = loadShader("glsl-vs");

	program = gl.createProgram();
	gl.attachShader(program, idFs);
	gl.attachShader(program, idVs);
	gl.linkProgram(program);

	if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
		alert("Could not create shader program");
	}

	gl.useProgram(program);
	return program;
}

function makeGeo() {
	console.log("Making geometry...");
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
	console.log("Drawing scene...");

	gl.bindBuffer(gl.ARRAY_BUFFER, geo);

	gl.enableVertexAttribArray(0);
	gl.vertexAttribPointer(0, 2, gl.FLOAT, false, 0, 0);
	gl.drawArrays(gl.TRIANGLES, 0, 3);
	gl.disableVertexAttribArray(0);
}

function loadImage() {
	image = new Image();
	image.onload = function() {
		console.log("Image downloaded...");

		var tex = gl.createTexture();
		gl.bindTexture(gl.TEXTURE_2D, tex);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		console.log("GL texture created...");

		console.log("Set program uniform...");
		var location = gl.getUniformLocation(program, "tex0");
		gl.uniform1i(location, 0);

		drawScene();
	}
	console.log("Downloading image...");
	image.src = "image.png";
}

function webGlStart() {
	var glcanvas = document.getElementById("glcanvas");
	initGl(glcanvas);

	program = makeShader();
	geo = makeGeo();

	loadImage();

	gl.clearColor(0.3, 0.4, 0.5, 1.0);
	gl.clear(gl.COLOR_BUFFER_BIT);
}



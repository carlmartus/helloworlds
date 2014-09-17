var renderer;
var cam;
var scene;
var cube;


function init() {
	renderer = new THREE.WebGLRenderer();
	renderer.setSize(window.innerwidth, window.innerheight);

	scene = new THREE.Scene();
	camera = new THREE.PerspectiveCamera(75, window.innerwidth/window.innerheight, 0.1, 1000);
	document.body.appendChild(renderer.domElement);
	var geometry = new THREE.BoxGeometry(1,1,1);
	var material = new THREE.MeshBasicMaterial({color: 0x00ff00});
	cube = new THREE.Mesh(geometry, material);
	scene.add(cube);
	camera.position.z = 5;

	render();
}

function render() {
	requestAnimationFrame(render);
	cube.rotation.x += 0.1;
	cube.rotation.y += 0.1;
	renderer.render(scene, camera);
}


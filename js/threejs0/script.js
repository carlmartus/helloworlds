function init() {
	var scene = new THREE.scene();
	var camera = new THREE.perspectivecamera(75, window.innerwidth/window.innerheight, 0.1, 1000);
	var renderer = new THREE.webglrenderer();
	renderer.setsize(window.innerwidth, window.innerheight);
	document.body.appendchild(renderer.domelement);
	var geometry = new THREE.boxgeometry(1,1,1);
	var material = new THREE.meshbasicmaterial({color: 0x00ff00});
	var cube = new THREE.mesh(geometry, material);
	scene.add(cube);
	camera.position.z = 5;

	var render = function () {
		requestanimationframe(render);
		cube.rotation.x += 0.1;
		cube.rotation.y += 0.1;
		renderer.render(scene, camera);
	};

	render();
}


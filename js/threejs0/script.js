function init() {
	var scene = new three.scene();
	var camera = new three.perspectivecamera(75, window.innerwidth/window.innerheight, 0.1, 1000);
	var renderer = new three.webglrenderer();
	renderer.setsize(window.innerwidth, window.innerheight);
	document.body.appendchild(renderer.domelement);
	var geometry = new three.boxgeometry(1,1,1);
	var material = new three.meshbasicmaterial({color: 0x00ff00});
	var cube = new three.mesh(geometry, material);
	scene.add(cube); camera.position.z = 5;
	var render = function () {
		requestanimationframe(render);
		cube.rotation.x += 0.1;
		cube.rotation.y += 0.1;
		renderer.render(scene, camera);
	};

	render();
}


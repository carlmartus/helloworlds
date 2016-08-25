'use strict';

function makeBaseTexture(url, linear) {
	var img = new Image();
	img.src = url;

	var base = new PIXI.BaseTexture(img,
			linear ? PIXI.SCALE_MODES.LINEAR : PIXI.SCALE_MODES.NEAREST);
	base.imageUrl = url;
	return base;
};

function createMatrix(baseTexture) {
	let texture = new PIXI.Texture(baseTexture,
			new PIXI.Rectangle(100, 100, 40, 30));
	let container = new PIXI.Container();

	for (let y=0; y<4; y++) {
		for (let x=0; x<4; x++) {
			let sp = new PIXI.Sprite(texture);
			sp.position.x = x*sp.width;
			sp.position.y = y*sp.height;
			container.addChild(sp);
		}
	}

	return container;
};

function main() {
	let renderer = PIXI.autoDetectRenderer(400, 300,
			{ backgroundColor: 0xff22ff44 });

	document.getElementById('drawArea').appendChild(renderer.view);

	// Sprite
	let base = makeBaseTexture('tumb.jpg', true);
	let tex = new PIXI.Texture(base);

	let sprite = new PIXI.Sprite(tex);
	sprite.buttonMode = true;
	sprite.position.y = 150;
	sprite.anchor.set(1.0);
	sprite.rotation = 1.0;
	sprite.interactive = true;
	sprite.on('mousedown', function() {
		sprite.scale.x += 0.1;
	});

	sprite.on('mouseover', function() {
	});

	sprite.on('mouseout', function() {
	});

	let startTime = Date.now();

	// Background 1/2
	let bgBase1 = makeBaseTexture('bg.jpg', false);
	let bgTex1 = new PIXI.Texture(bgBase1);
	let bgTiling1 = new PIXI.extras.TilingSprite(bgTex1,
			renderer.width, renderer.height);

	// Background 2/2
	let bgBase2 = makeBaseTexture('moln.png', false);
	let bgTex2 = new PIXI.Texture(bgBase2);
	let bgTiling2 = new PIXI.extras.TilingSprite(bgTex2,
			renderer.width, renderer.height);

	// Matrix
	let matrix = createMatrix(base);

	// Scene
	let stage = new PIXI.Container();
	stage.addChild(bgTiling1);
	stage.addChild(bgTiling2);
	stage.addChild(sprite);
	stage.addChild(matrix);


	function animate() {
		let now = Date.now();
		let passed = (now - startTime) * 0.001;

		sprite.position.x = passed*10.5;
		bgTiling1.tilePosition.x = Math.floor(-passed*40.0);
		bgTiling1.tilePosition.y = -50;
		bgTiling1.worldTransform.tx = -0.5;
        bgTiling1.worldTransform.ty = -0.5;

		bgTiling2.tilePosition.x = Math.floor(-passed*10.0);

		renderer.render(stage);
		requestAnimationFrame(animate);
	};

	animate();
};


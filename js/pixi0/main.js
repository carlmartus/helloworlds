'use strict';

function makeBaseTexture(url, linear) {
	var img = new Image();
	img.src = url;

	var base = new PIXI.BaseTexture(img,
			linear ? PIXI.SCALE_MODES.LINEAR : PIXI.SCALE_MODES.NEAREST);
	base.imageUrl = url;
	return base;
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

	let startTime = Date.now();

	// Background
	let bgBase = makeBaseTexture('bg.jpg', false);
	let bgTex = new PIXI.Texture(bgBase);
	let bgTiling = new PIXI.extras.TilingSprite(bgTex,
			renderer.width, renderer.height);
	//bgTiling._tileScaleOffset.x = 0;

	// Scene
	let stage = new PIXI.Container();
	stage.addChild(bgTiling);
	stage.addChild(sprite);


	function animate() {
		let now = Date.now();
		let passed = (now - startTime) * 0.001;

		sprite.position.x = passed*10.5;
		bgTiling.tilePosition.x = Math.floor(-passed*40.0);
		bgTiling.tilePosition.y = -50;
		bgTiling.worldTransform.tx = -0.5;
        bgTiling.worldTransform.ty = -0.5;

		renderer.render(stage);
		requestAnimationFrame(animate);
	};

	animate();
};


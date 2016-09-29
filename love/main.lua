local x, font;

function love.load()
	love.graphics.setBackgroundColor(0x7f, 0x7f, 0x7f)

	x = 50;
	--font = love.graphics.newFont("boogie.ttf", 60)

	font = love.graphics.newImageFont("font.png", "ehlo")
	love.graphics.setFont(font)

	swordImage = love.graphics.newImage("sword.png")
	swordImage:setMipmapFilter("nearest", 0)
	swordImage:setFilter("nearest", "nearest")
end

function love.keypressed(key)
	if key == 'q' then
		love.event.quit()
	end
end

function love.resize()
	print "RESIZE"
end

function love.draw()
	love.graphics.print('hello', x, 300)
	love.graphics.draw(swordImage, 100, 100, 0.02 * x, 3, 3, 16, 8)
	x = x+1;
end


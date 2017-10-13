// Exercice IO 2.1
// Written by Léon Chabbey

#include <SFML/Graphics.hpp>
#include <iostream>

#define RECT_SIZE 100
#define CIRCLE_RADIUS 50

sf::Vector2f randomWindowPosition(sf::Window& window, float xOffset = 0.f, float yOffset = 0.f) {
	const int WINDOW_WIDTH = window.getSize().x,
		WINDOW_HEIGHT = window.getSize().y;

	float randX = xOffset ? rand() % (int)(WINDOW_WIDTH - xOffset) : rand() % WINDOW_WIDTH;
	float randY = yOffset ? rand() % (int)(WINDOW_WIDTH - yOffset) : rand() % WINDOW_HEIGHT;

	return sf::Vector2f(randX, randY);
}

bool areRectAndCircleColliding(sf::RectangleShape& rect, sf::CircleShape& circle) {
	sf::Vector2f rectPosition = rect.getPosition(),
		circlePosition = circle.getPosition(),
		rectSize = rect.getSize();

	// The circle's anchor point x/y is by default at the top left of the
	// "virtual square" around him. It needs to be in the circle's middle to work.
	circlePosition.x += circle.getRadius();
	circlePosition.y += circle.getRadius();

	float deltaX = circlePosition.x - fmaxf(rectPosition.x, fminf(circlePosition.x, rectPosition.x + rectSize.x));
	float deltaY = circlePosition.y - fmaxf(rectPosition.y, fminf(circlePosition.y, rectPosition.y + rectSize.y));

	return (deltaX * deltaX + deltaY * deltaY) < pow(circle.getRadius(), 2);
}

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	window.setFramerateLimit(60);

	float speed = 5.f;

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(RECT_SIZE, RECT_SIZE));
	rect.setPosition(window.getSize().x/2 - rect.getSize().x/2, 
					window.getSize().y/2 - rect.getSize().y/2);

	sf::CircleShape circle(CIRCLE_RADIUS);
	circle.setPosition(randomWindowPosition(window, CIRCLE_RADIUS*2, CIRCLE_RADIUS*2));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// check if shapes are colliding
		if (areRectAndCircleColliding(rect, circle)) {
			rect.setFillColor(sf::Color::Red);
			circle.setFillColor(sf::Color::Red);
		}
		else {
			rect.setFillColor(sf::Color::Blue);
			circle.setFillColor(sf::Color::Green);
		}


		// Circle Movement
		sf::Vector2f deltaMove;

		bool circleOffscreenWindowLeft = circle.getPosition().x > 0.f,
			circleOffscreenWindowRight = circle.getPosition().x < window.getSize().x - circle.getRadius() * 2,
			circleOffscreenWindowTop = circle.getPosition().y > 0.f,
			circleOffscreenWindowBottom = circle.getPosition().y < window.getSize().y - circle.getRadius() * 2;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && circleOffscreenWindowLeft)
			deltaMove.x -= 1.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && circleOffscreenWindowRight)
			deltaMove.x += 1.0f;
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && circleOffscreenWindowTop)
			deltaMove.y -= 1.0f;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && circleOffscreenWindowBottom)
			deltaMove.y += 1.0f;

		circle.setPosition(circle.getPosition() + speed*deltaMove);

		window.clear();
		window.draw(rect);
		window.draw(circle);
		window.display();
	}

	return 0;
}
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>


int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "IK Demo");

	sf::RectangleShape rect(sf::Vector2f(50.0f, 50.0f));
	rect.setPosition(sf::Vector2f(100.0f , 100.0f));

	sf::Vector2f pos2;
	sf::RectangleShape rect2(sf::Vector2f(50.0f, 50.0f));
	rect2.setOrigin(rect2.getSize()/2.0f);
	rect2.setPosition(sf::Vector2f(100.0f, 100.0f));
	pos2 = rect2.getPosition();

	sf::ConvexShape rect3(4);
	rect3.setPoint(0, sf::Vector2f(0, 0));
	rect3.setPoint(1, sf::Vector2f(10, 0));
	rect3.setPoint(2, sf::Vector2f(10, 10));
	rect3.setPoint(3, sf::Vector2f(0, 10));
	rect3.setPosition(200, 200);

	NewObject rect4(sf::Vector2f(500, 500), sf::Vector2f(50, 50));

	sf::Clock clock;
	const unsigned int fps = 60;
	const float timeStep = 1.0f / fps;
	float accumulatedTime = 0.0f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				
				break;
			case sf::Event::MouseButtonPressed:
				
				break;
			case sf::Event::MouseMoved:
				
				break;
			default:
				break;
			}
		}

		float elapsedTime = clock.restart().asSeconds();

		if (elapsedTime > 0.25f) {
			elapsedTime = 0.25f;
		}

		accumulatedTime += elapsedTime;

		while (accumulatedTime >= timeStep) {
			//update
			accumulatedTime -= timeStep;
			//pos2 = rect2.getPosition();
			//rect2.setPosition(-100.0f, -100.0f);
			//rect2.setSize(rect2.getSize() + sf::Vector2f(0.1f, 0.1f));
			//rect2.setPosition(pos2);
			//rect2.scale(1.01f, 1.01f);
			//rect3.setPoint(1, sf::Vector2f(sf::Mouse::getPosition(window).x - rect3.getPosition().x, 0.0f));
			//rect3.setPoint(2, (sf::Vector2f)sf::Mouse::getPosition(window) - rect3.getPosition());
			//rect3.setPoint(3, sf::Vector2f(0.0f, sf::Mouse::getPosition(window).y - rect3.getPosition().y));
			//std::cout << rect2.getSize().x << std::endl;

			rect4.ReSize(sf::Vector2f(0.1f, 0.0f), 0);
		}
		//render
		window.clear(sf::Color::Black);
		window.draw(rect3);
		window.draw(rect);
		window.draw(rect2);
		window.draw(rect4);
		window.display();
	}
	system("pause");
	return EXIT_SUCCESS;
}
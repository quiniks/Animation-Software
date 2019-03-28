#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

#include "InteractionPtrs.h"
#include <Button.h>
#include <Canvas.h>
#include <ToolBox.h>
#include <Camera.h>
#include <Object.h>
#include <list>
#include <any>
#include <InputHandler.h>
#include <KeyframeManager.h>
#include <TimeLineViewer.h>
#include <Shapes.h>
#include <Timer.h>
#include <ScrollBox.h>
#include <TimeLine.h>

void close() {
	std::cout << "close" << std::endl;
}

void keypre() {
	std::cout << "doot" << std::endl;
}

void move(std::vector<std::any> p_Args) {
	sf::Vector2i l_Pos = std::any_cast<sf::Vector2i>(p_Args[0]);
	std::cout << "movdd: " << l_Pos.x << " / " << l_Pos.y << std::endl;
}

void move2(sf::Vector2i p_Pos) {
	static bool test = false;
	std::cout << "movdd: " << p_Pos.x << " / " << p_Pos.y << std::endl;

}

void clk(std::vector<std::any> p_Args) {
	std::cout << "oof" << std::endl;
}

int main() {
	
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Animation Project", sf::Style::Titlebar | sf::Style::Close);
	SFMLInputHandler inputHandler;

	Canvas canvas(&window);
	Camera camera(sf::Vector2f(1080.0f/4.0f, 720.0f/3.0f), sf::Vector2f(1080.0f, 720.0f));

	Shapes m_Shapes;
	//m_Shapes.NewShape(Object(ShapeType::RectangleType, sf::Vector2f(10, 10), sf::Vector2f(50.0f, 50.0f)));

	sf::Clock clock;
	const unsigned int fps = 60;
	const float timeStep = 1.0f / fps;
	float accumulatedTime = 0.0f;
	
	std::vector<Object*> objects;
	InteractionPtrs * subsystemPointers = new InteractionPtrs(&objects, &m_Shapes, &window, &camera);
	
	std::list<Button> buttons;
	buttons.emplace_back("DrawButtonClicked", "Assets/Images/DrawButtonImage.png", sf::Vector2f(1.0f, 1.0f), sf::Vector2f(20.0f, 20.0f));
	buttons.emplace_back("TransformButtonClicked", "Assets/Images/TransformButtonImage.png", sf::Vector2f(22.0f, 1.0f), sf::Vector2f(20.0f, 20.0f));
	buttons.emplace_back("ColourButtonClicked", "Assets/Images/ColourButtonImage.png", sf::Vector2f(43.0f, 1.0f), sf::Vector2f(20.0f, 20.0f));
	buttons.emplace_back("JointButtonClicked", "Assets/Images/JointButtonImage.png", sf::Vector2f(64.0f, 1.0f), sf::Vector2f(20.0f, 20.0f));

	buttons.emplace_back("Play", "Assets/Images/PlayButtonIcon.png", sf::Vector2f(85.0f, 1.0f), sf::Vector2f(20.0f, 20.0f));
	buttons.emplace_back("Stop", "Assets/Images/StopButtonIcon.png", sf::Vector2f(106.0f, 1.0f), sf::Vector2f(20.0f, 20.0f));
	buttons.emplace_back("Record", "Assets/Images/RecordButtonIcon.png", sf::Vector2f(127.0f, 1.0f), sf::Vector2f(20.0f, 20.0f));
	
	sf::RectangleShape buttonBar;
	buttonBar.setSize(sf::Vector2f(1080, 23));
	buttonBar.setFillColor(sf::Color(150, 150, 150, 255));

	ToolBox toolBox(subsystemPointers);

	KeyframeManager keyframeManager(10, 30, &m_Shapes);
	TimeLine m_TimeLine(sf::Vector2f(0, 24), sf::Vector2f(1080, 100), 10, keyframeManager.GetTotalFrames());

	std::function<void(const flat_set<ShapeKeyFrames, CompareId>&, FrameState)> l_KeyFrameAddedCB = std::bind(&TimeLine::Update, &m_TimeLine, std::placeholders::_1, std::placeholders::_2);
	std::function<void(unsigned int)> l_SetKeyFrameCB = std::bind(&KeyframeManager::SetCurrentFrame, &keyframeManager, std::placeholders::_1);
	m_TimeLine.SetKeyFrame.Connect(l_SetKeyFrameCB);
	keyframeManager.OnUpdate.Connect(l_KeyFrameAddedCB);

	int i = 0;
	int j = 0;
	std::cout << ++i << "/" << j++ << std::endl;

	///////////////////////////////////////////////////////

	while (window.isOpen())
	{
		inputHandler.HandleInputs(window, camera);

		float elapsedTime = clock.restart().asSeconds();
		//test.Update(-elapsedTime);
		if (elapsedTime > 0.25f) {
			elapsedTime = 0.25f;
		}

		accumulatedTime += elapsedTime;

		while (accumulatedTime >= timeStep) {
			//update/////////////////
			keyframeManager.Update();
			toolBox.Update(timeStep);
			canvas.Update();
			accumulatedTime -= timeStep;
		}
		//render///////////////////

		canvas.Clear(sf::Color::White);
		window.clear(sf::Color(100, 100, 100, 255));
		//Handle view rendering
		window.setView(camera);
		for (Object *i : objects) {
			i->UpdateShape();
			canvas.Draw(*i);
		}
		m_Shapes.UpdateShapes();
		canvas.Draw(m_Shapes);
		canvas.Display();
		window.draw(canvas);
		//Handle screen rendering
		window.setView(window.getDefaultView());
		window.draw(toolBox);
		//window.draw(colourPanel);
		window.draw(buttonBar);
		//timeLineViewer.Update();
		//window.draw(timeLineViewer);
		window.draw(m_TimeLine);
		for (Button& button : buttons) {
			window.draw(button);
		}
		//window.draw(m_Shapes);
		window.display();
		//system("cls");
	}
	//system("pause");
	return EXIT_SUCCESS;
}
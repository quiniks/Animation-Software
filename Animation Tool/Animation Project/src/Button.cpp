#include "..\include\Button.h"

void Button::OnMouseClick(bool p_State)
{
	if (m_isOver) {
		if (p_State) {
			setFillColor(sf::Color(100, 100, 100, 255));
			onClicked.Notify();
		}
		else {
			setFillColor(sf::Color(200, 200, 200, 255));
		}
	}
}

void Button::OnMouseMove(sf::Vector2i p_Pos)
{
	if (getGlobalBounds().contains((sf::Vector2f)(p_Pos))) {
		setFillColor(sf::Color(200, 200, 200, 255));
		onAnyButtonOver.Notify(true);
		m_isOver = true;
	} else {
		setFillColor(sf::Color::White);
		onAnyButtonOver.Notify(false);
		m_isOver = false;
	}
}

Button::Button(std::string p_SignalName, std::string p_IconFilePath, const sf::Vector2f & p_Pos, const sf::Vector2f & p_Size)
{
	std::function<void(sf::Vector2i)> test1 = std::bind(&Button::OnMouseMove, this, std::placeholders::_1);
	std::function<void(bool)> test2 = std::bind(&Button::OnMouseClick, this, std::placeholders::_1);
	EventHandlerInstance.Connect2("MouseMoved", test1);
	EventHandlerInstance.Connect2("LMB", test2);
	EventHandlerInstance.Register2(p_SignalName, &onClicked);
	EventHandlerInstance.Register2("AnyButtonOver", &onAnyButtonOver);
	setPosition(p_Pos);
	setSize(p_Size);
	setFillColor(sf::Color::White);

	sf::RectangleShape l_RectBg(sf::Vector2f(20, 20));
	sf::RectangleShape l_RectIcon(sf::Vector2f(20, 20));
	sf::Texture l_TexBg;
	sf::Texture l_TexIcon;
	if (!l_TexBg.loadFromFile("Assets/Images/ButtonImage.png") || !l_TexIcon.loadFromFile(p_IconFilePath)) {
		std::cout << "textures not loaded" << std::endl;
	}
	//l_TexIcon.loadFromFile(p_IconFilePath);
	l_TexBg.setSmooth(true);
	l_RectBg.setTexture(&l_TexBg);
	l_RectIcon.setTexture(&l_TexIcon);

	sf::RenderTexture l_RenderTexture;
	l_RenderTexture.create(20, 20);
	l_RenderTexture.draw(l_RectBg);
	l_RenderTexture.draw(l_RectIcon);
	l_RenderTexture.display();
	sf::Texture* l_TexButton = new sf::Texture(l_RenderTexture.getTexture());
	setTexture(l_TexButton);
}
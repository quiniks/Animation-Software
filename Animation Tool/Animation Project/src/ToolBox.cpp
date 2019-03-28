#include "..\include\ToolBox.h"

ToolBox::ToolBox(InteractionPtrs * p_pSP) : HasInteractionPtrs(p_pSP)
{
	std::function<void(sf::Vector2i, sf::Vector2f)> test1 = std::bind(&ToolBox::OnMouseMove, this, std::placeholders::_1, std::placeholders::_2);
	std::function<void(sf::Mouse::Button, bool)> test2 = std::bind(&ToolBox::OnMouseClick, this, std::placeholders::_1, std::placeholders::_2);
	std::function<void(bool)> test3 = std::bind(&ToolBox::SetActive, this, std::placeholders::_1);

	std::function<void()> selectDrawTool = std::bind(&ToolBox::SelectDraw, this);
	std::function<void()> selectTransformTool = std::bind(&ToolBox::SelectTransform, this);
	std::function<void()> selectColourTool = std::bind(&ToolBox::SelectColour, this);
	std::function<void()> selectJointTool = std::bind(&ToolBox::SelectJoint, this);

	EventHandlerInstance.Connect2("DrawButtonClicked", selectDrawTool);
	EventHandlerInstance.Connect2("TransformButtonClicked", selectTransformTool);
	EventHandlerInstance.Connect2("ColourButtonClicked", selectColourTool);
	EventHandlerInstance.Connect2("JointButtonClicked", selectJointTool);
	EventHandlerInstance.Connect2("MouseMovedExtra", test1);
	EventHandlerInstance.Connect2("MouseButton", test2);
	EventHandlerInstance.Connect2("AnyButtonOver", test3);

	m_Tools.emplace("Draw", new ShapeTool(getSubsystemPointers()));
	m_Tools.emplace("Transform", new TransformTool(getSubsystemPointers()));
	m_Tools.emplace("Colour", new ColourTool(getSubsystemPointers()));
	m_Tools.emplace("Joint", new JointTool(getSubsystemPointers()));
	m_pSelectedTool = m_Tools["Draw"];
}

ToolBox::~ToolBox()
{
	for (auto &l_Tool : m_Tools) {
		delete l_Tool.second;
	}
}

void ToolBox::Update(float p_DeltaTime)
{
	if (m_pSelectedTool != nullptr) {
		m_pSelectedTool->Update(p_DeltaTime);
	}
}

void ToolBox::OnMouseClick(sf::Mouse::Button p_Button, bool p_State)
{
	if (m_pSelectedTool != nullptr) {
		m_pSelectedTool->OnMouseClick(p_Button, p_State);
	}
}

void ToolBox::OnMouseMove(sf::Vector2i p_WindowPos, sf::Vector2f p_WorldPos)
{
	if (m_pSelectedTool != nullptr) {
		m_pSelectedTool->OnMouseMove(p_WindowPos, p_WorldPos);
	}
}


void ToolBox::SetActive(bool p_bActive)
{
	if (m_pSelectedTool != nullptr) {
		m_pSelectedTool->m_Active = !p_bActive;
	}
}

void ToolBox::SelectDraw()
{
	//delete m_pSelectedTool;
	//m_pSelectedTool->m_Active = false;
	m_pSelectedTool = m_Tools["Draw"];
	//m_pSelectedTool->m_Active = true;
}

void ToolBox::SelectTransform()
{
	//delete m_pSelectedTool;
	//m_pSelectedTool->m_Active = false;
	m_pSelectedTool = m_Tools["Transform"];
	//m_pSelectedTool->m_Active = true;
}

void ToolBox::SelectColour()
{
	//delete m_pSelectedTool;
	//m_pSelectedTool->m_Active = false;
	m_pSelectedTool = m_Tools["Colour"];
	//m_pSelectedTool->m_Active = true;
}

void ToolBox::SelectJoint()
{
	//delete m_pSelectedTool;
	//m_pSelectedTool->m_Active = false;
	m_pSelectedTool = m_Tools["Joint"];
	//m_pSelectedTool->m_Active = true;
}

void ToolBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_pSelectedTool != nullptr) {
		target.draw(*m_pSelectedTool);
	}
}

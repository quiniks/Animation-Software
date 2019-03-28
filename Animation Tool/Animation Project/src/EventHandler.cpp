#include "..\include\EventHandler.h"

EventHandler & EventHandler::Instance()
{
	static EventHandler instance;
	return instance;
}

void EventHandler::Register(std::string p_SignalName, Signal2 * p_Signal)
{
	m_EventMap.insert(std::pair<std::string, Signal2*>(p_SignalName, p_Signal));
}

void EventHandler::Connect(std::string p_SignalName, std::function<void(std::vector<std::any>)> p_Listener)
{
	m_EventMap[p_SignalName]->Connect(p_Listener);
}

void EventHandler::Disconnect(std::string p_SignalName, unsigned int p_ID)
{
	m_EventMap[p_SignalName]->Disconnect(p_ID);
}

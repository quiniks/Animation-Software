#pragma once
#include <SFML/Graphics.hpp>
#include "Signal.h"
#include <any>
#include <iostream>

#define EventHandlerInstance EventHandler::Instance()

class EventHandler {
private:
	std::map<std::string, Signal2*> m_EventMap;
	std::map<std::string, std::any> m_EventMap2;
	EventHandler() = default;
	~EventHandler() = default;
public:
	static EventHandler &Instance();
	EventHandler(EventHandler const&) = delete; //!< Copy operator.
	EventHandler& operator= (EventHandler const&) = delete; //!< Assignment operator. 
	void Register(std::string p_SignalName, Signal2* p_Signal);
	void Connect(std::string p_SignalName, std::function<void(std::vector<std::any>)> p_Listener);
	template<typename... Args>
	void Register2(std::string p_SignalName, Signal<Args...>* p_Signal) {
		//std::cout << p_Signal << std::endl;
		m_EventMap2.insert(std::pair<std::string, std::any>(p_SignalName, p_Signal));
		//std::cout << std::any_cast<Signal<Args...>*>(m_EventMap2.at("MouseMoved")) << std::endl;
	}
	template<typename... Args>
	int Connect2(std::string p_SignalName, std::function<void(Args...)> const& p_Listener) {
		Signal<Args...>* l_Signal = std::any_cast<Signal<Args...>*>(m_EventMap2.at(p_SignalName));
		return l_Signal->Connect(p_Listener);
		//std::cout << std::any_cast<Signal<Args...>*>(m_EventMap2.at("MouseMoved")) << std::endl;
		//std::any_cast<Signal<Args...>*>(m_EventMap2.at(p_SignalName))
	}

	void Disconnect(std::string p_SignalName, unsigned int p_ID);
};

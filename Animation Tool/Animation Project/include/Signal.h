#pragma once

#include <functional>
#include <map>
#include <vector>
#include <any>

#define FUNC_PTR std::function<void(Args...)>
#define FUNC_PTR_ANY std::function<void(std::vector<std::any>)>
/**
 * @class Signal
 * @brief Handles the connections of call back functions
 */
template <typename... Args>
class Signal {
private:
	//! The ID of the signal
	mutable int m_ID;
	//! The map of IDs and callback function pointers
	mutable std::map<int, FUNC_PTR> m_Listeners;
public:
	//! Constructor sets the ID to 0
	Signal() : m_ID(0) {}
	//! Copy constructor makes sure the ID is still 0
	Signal(Signal const& p_Signal) : m_ID(0) {}
	//! Connection method takes a std::functional function pointer and emplaces it to the map
	int Connect(FUNC_PTR const&  p_Listener) const {
		m_Listeners.emplace(++m_ID, p_Listener);
		return m_ID;
	};
	//! Disconnect method erases a callback with ID p_ID
	void Disconnect(int p_ID) const {
		m_Listeners.erase(p_ID);
	};
	//! Disconnect all callback functions
	void DisconectAll() const {
		m_Listeners.clear();
	};
	//! Calls and passes the given arguments to all callback functions
	void Notify(Args... p_Args) {
		for (auto l_Listeners : m_Listeners) {
			l_Listeners.second(p_Args...);
		}
	};
	//! Overloaded assignment operator disconnects all callbacks
	Signal& operator=(Signal const& p_Signal) {
		this->DisconnectAll();
	};
};

class Signal2 {
private:
	mutable int m_ID;
	mutable std::map<int, FUNC_PTR_ANY> m_Listeners;
public:
	Signal2() : m_ID(0) {}
	Signal2(Signal2 const& p_Signal) : m_ID(0) {}

	int Connect(FUNC_PTR_ANY const& p_Listener) const {
		m_Listeners.insert(std::make_pair(++m_ID, p_Listener));
		return m_ID;
	};
	void Disconnect(int p_ID) const {
		m_Listeners.erase(p_ID);
	};
	void DisconectAll() const {
		m_Listeners.clear();
	};
	void Notify(std::vector<std::any> p_Args) {
		for (auto l_Listeners : m_Listeners) {
			l_Listeners.second(p_Args);
		}
	};
	Signal2& operator=(Signal2 const& p_Signal) {
		this->DisconectAll();
	};
};

class Signal3 {
private:
	mutable int m_ID;
	mutable std::map<int, std::function<void()>> m_Listeners;
public:
	Signal3() : m_ID(0) {}
	Signal3(Signal3 const& p_Signal) : m_ID(0) {}

	template<typename ...Args>
	int Connect(FUNC_PTR const& p_Listener) const
	{
		m_Listeners.insert(std::make_pair(++m_ID, p_Listener));
		return m_ID;
	}
	void Disconnect(int p_ID) const {
		m_Listeners.erase(p_ID);
	};
	void DisconectAll() const {
		m_Listeners.clear();
	};
	template<typename ...Args>
	void Notify(Args... p_Args)
	{
		for (auto l_Listeners : m_Listeners) {
			l_Listeners.second(p_Args...);
		}
	}
	Signal3& operator=(Signal3 const& p_Signal) {
		this->DisconectAll();
	};
};

template <typename ...Args>
class AbstractDelegate {
public:
	virtual void Call(Args... p_Args) = 0;
};
#pragma once

#include <functional>
#include <map>
#include <vector>
#include <any>

#define FUNC_PTR std::function<void(Args...)>
#define FUNC_PTR_ANY std::function<void(std::vector<std::any>)>

template <typename... Args>
class Signal {
private:
	mutable int m_ID;
	mutable std::map<int, FUNC_PTR> m_Listeners;
	//Args... Args{};
public:
	Signal() : m_ID(0) {}
	Signal(Signal const& p_Signal) : m_ID(0) {}

	int Connect(FUNC_PTR const&  p_Listener) const {
		m_Listeners.emplace(++m_ID, p_Listener);
		return m_ID;
	};
	void Disconnect(int p_ID) const {
		m_Listeners.erase(p_ID);
	};
	void DisconectAll() const {
		m_Listeners.clear();
	};
	void Notify(Args... p_Args) {
		for (auto l_Listeners : m_Listeners) {
			l_Listeners.second(p_Args...);
		}
	};
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



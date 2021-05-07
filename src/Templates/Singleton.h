#pragma once

///@brief Pattern class for Singleton needs.
///@note The inheritanced class should make 'Singleton' friend to access it's private constructor.
template<class T>
class Singleton
{
public:
	virtual ~Singleton() = default;
	static T &getInstance();
};

template<typename T>
T &Singleton<T>::getInstance()
{
	static T instance;
	return instance;
}

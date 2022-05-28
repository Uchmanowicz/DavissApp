#pragma once

namespace Templates
{
	///@brief Pattern class for Singleton needs.
	///@note The inheritanced class should make 'Singleton' friend to access it's private constructor.
	///@note The inheritanced class should delete: default constructor, copy constructor, copy assignment operator.
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
}

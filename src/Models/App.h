#pragma once

#include <QObject>

class App
{   
public:
	Q_GADGET

public:
	enum Appearance
	{
		BLUE = 0,
		RED
	};
	Q_ENUM(Appearance);

	Q_PROPERTY(Appearance ui_appearance MEMBER appearance);
	Q_PROPERTY(bool ui_synchronizing MEMBER sync);

public:
	App() {}
	App(const Appearance &appearance_, const bool &sync_ = true)
		: appearance(appearance_), sync(sync_)
	{}

	Appearance appearance = Appearance::BLUE;
	bool sync = true;


	bool operator==(const App &other) const
	{
		return appearance == other.appearance
				&& sync == other.sync;
	}

	bool operator!=(const App &other) const
	{
		return appearance != other.appearance
				|| sync != other.sync;
	}
};
Q_DECLARE_METATYPE(App::Appearance)

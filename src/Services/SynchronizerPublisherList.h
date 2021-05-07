#pragma once

#include "Templates/SynchronizerHandler.h"

struct SynchronizerPublisherList : public Publisher<IUserSync>, public Publisher<IJobSync>
{
	~SynchronizerPublisherList() {}
	using Publisher<IUserSync>::addListener;
	using Publisher<IUserSync>::removeListener;
	using Publisher<IJobSync>::addListener;
	using Publisher<IJobSync>::removeListener;

};



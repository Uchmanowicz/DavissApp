#pragma once

#include "Templates/SynchronizerHandler.h"
namespace Sync
{
	struct SynchronizerPublisherList : public Templates::Publisher<Listeners::IUserSync>, public Templates::Publisher<Listeners::IJobSync>
	{
		~SynchronizerPublisherList() { }
		using Templates::Publisher<Listeners::IUserSync>::addListener;
		using Templates::Publisher<Listeners::IUserSync>::removeListener;
		using Templates::Publisher<Listeners::IJobSync>::addListener;
		using Templates::Publisher<Listeners::IJobSync>::removeListener;
	};
}

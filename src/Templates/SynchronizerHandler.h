#pragma once

#include "Templates/Publisher.h"

namespace Listeners
{
	struct IUserSync
	{
		virtual ~IUserSync() { }
		virtual void onSynced() = 0;
	};

	struct IJobSync
	{
		virtual ~IJobSync() { }
		virtual void onSynced() = 0;
	};

	template<class _ObjType>
	struct ILocalSyncUpdates
	{
		// TODO
		enum UpdateType
		{
			USER = 0,
			APP
		};

		virtual ~ILocalSyncUpdates() { }
		virtual void onLocalUpdates(const _ObjType &obj) = 0;
	};
}

namespace Templates
{
	template<class _ObjType>
	struct SynchronizerHandler : public Templates::Publisher<Listeners::ILocalSyncUpdates<_ObjType>>
	{
		virtual ~SynchronizerHandler() { }
	};
}

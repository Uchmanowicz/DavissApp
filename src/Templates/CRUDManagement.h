#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Resources/DatabaseStatus.h"

namespace Templates
{
	template<typename Key, typename Obj>
	class CRUDLocalManagement
	{
	public:
		CRUDLocalManagement() = default;
		virtual ~CRUDLocalManagement() = default;
		virtual Obj select(const Key &key, DB::Status *status = nullptr) const = 0;
		virtual std::vector<Obj> selectAll(DB::Status *status = nullptr) const = 0;
		virtual bool insert(const Obj &obj, DB::Status *status = nullptr) = 0;
		virtual bool remove(const Obj &obj, DB::Status *status = nullptr) = 0;
		virtual bool removeAll(DB::Status *status = nullptr) = 0;
		virtual bool update(const Obj &obj, DB::Status *status = nullptr) = 0;
	};

	template<typename Key, typename Obj>
	class CRUDWebManagement
	{
	public:
		CRUDWebManagement() = default;
		virtual ~CRUDWebManagement() = default;
		virtual Obj selectWeb(const Key &key, DB::Status *status = nullptr) const = 0;
		virtual std::vector<Obj> selectAllWeb(DB::Status *status = nullptr) const = 0;
		virtual bool insertWeb(const Obj &obj, DB::Status *status = nullptr) = 0;
		virtual bool removeWeb(const Obj &obj, DB::Status *status = nullptr) = 0;
		virtual bool removeAllWeb(DB::Status *status = nullptr) = 0;
		virtual bool updateWeb(const Obj &obj, DB::Status *status = nullptr) = 0;
	};
}

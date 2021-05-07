#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Resources/DatabaseStatus.h"

template<typename Key, typename Obj>
class CRUDLocalManagement
{
public:
	CRUDLocalManagement() = default;
	virtual ~CRUDLocalManagement() = default;
	virtual Obj select(const Key &key, DBStatus::StatusType *status = nullptr) const = 0;
	virtual std::vector<Obj> selectAll(DBStatus::StatusType *status = nullptr) const = 0;
	virtual bool insert(const Obj &obj, DBStatus::StatusType *status = nullptr) = 0;
	virtual bool remove(const Obj &obj, DBStatus::StatusType *status = nullptr) = 0;
	virtual bool removeAll(DBStatus::StatusType *status = nullptr) = 0;
	virtual bool update(const Obj &obj, DBStatus::StatusType *status = nullptr) = 0;
};

template<typename Key, typename Obj>
class CRUDWebManagement
{
public:
	CRUDWebManagement() = default;
	virtual ~CRUDWebManagement() = default;
	virtual Obj selectWeb(const Key &key, DBStatus::StatusType *status = nullptr) const = 0;
	virtual std::vector<Obj> selectAllWeb(DBStatus::StatusType *status = nullptr) const = 0;
	virtual bool insertWeb(const Obj &obj, DBStatus::StatusType *status = nullptr) = 0;
	virtual bool removeWeb(const Obj &obj, DBStatus::StatusType *status = nullptr) = 0;
	virtual bool removeAllWeb(DBStatus::StatusType *status = nullptr) = 0;
	virtual bool updateWeb(const Obj &obj, DBStatus::StatusType *status = nullptr) = 0;
};

//#pragma once

////#include "LocalManagement.h"

// template <typename Obj>
// LocalManagement<Obj>::LocalManagement(const QSqlDatabase &database)
//	: m_database(database)
//{
//	if(!m_database.isOpen()) {
//		if(!m_database.open()) {
//			fetchError(m_database.lastError());
//		}
//	}
// }

// template <typename Obj>
// LocalManagement<Obj>::~LocalManagement()
//{
// }

// template <typename Obj>
// QSqlRecord LocalManagement<Obj>::select(const Query &query, DBDB::StatusType *status) const
//{
//	QString sql(query.query.c_str());
//	QSqlQuery sqlQuery(m_database);

//	if(sqlQuery.prepare(sql)) {
//		if(sqlQuery.exec()) {
//			*status = DBStatus::OK;
//			if(sqlQuery.next()) {
//				return sqlQuery.record();
//			}else {
//				return QSqlRecord();
//			}
//		}
//	}

//	fetchError(sqlQuery.lastError(), status);
//	return QSqlRecord();
//}

// template <typename Obj>
// std::vector<QSqlRecord> LocalManagement<Obj>::selectAll(const Query<Obj> &query, DBDB::StatusType *status) const
//{
//	QString sql(query.query.c_str());
//		QSqlQuery sqlQuery(m_database);

//		if(sqlQuery.prepare(sql)) {
//			if(sqlQuery.exec()) {
//				std::vector<QSqlRecord> objs;
//				while(sqlQuery.next()) {
//					objs.push_back(sqlQuery.record());
//				}
//				*status = DBStatus::OK;
//				return objs;
//			}
//		}

//		fetchError(sqlQuery.lastError(), status);
//		return {};
//}

// template <typename Obj>
// bool LocalManagement<Obj>::insert(const Query<Obj> &query, DBDB::StatusType *status)
//{
//		QString sql(query.query.c_str());

//		QSqlQuery sqlQuery(m_database);

//		if(sqlQuery.prepare(sql)) {
//			if(sqlQuery.exec()) {
//				*status = DBStatus::OK;
//				return true;
//			}
//		}

//		fetchError(sqlQuery.lastError(), status);
//		return false;
//}

// template <typename Obj>
// bool LocalManagement<Obj>::remove(const Query<Obj> &query, DBDB::StatusType *status)
//{
//	QString sql(query.query.c_str());
//	QSqlQuery sqlQuery(m_database);

//	if(sqlQuery.prepare(sql)) {
//		if(sqlQuery.exec()) {
//			*status = DBStatus::OK;
//			return true;
//		}

//		fetchError(sqlQuery.lastError(), status);
//		return false;
//	}
//}

// template <typename Obj>
// bool LocalManagement<Obj>::removeAll(const Query<Obj> &query, DBDB::StatusType *status)
//{
//	QString sql(query.query.c_str());
//	QSqlQuery sqlQuery(m_database);

//	if(sqlQuery.prepare(sql)) {
//		if(sqlQuery.exec()) {
//			*status = DBStatus::OK;
//			return true;
//		}

//		fetchError(sqlQuery.lastError(), status);
//		return false;
//	}
//}

// template <typename Obj>
// bool LocalManagement<Obj>::update(const Query<Obj> &query, DBDB::StatusType *status)
//{
//		QString sql(query.query.c_str());
//		QSqlQuery sqlQuery(m_database);

//		if(sqlQuery.prepare(sql)) {
//			if(sqlQuery.exec()) {
//				fetchError(sqlQuery.lastError(), status);
//				*status = DBStatus::OK;
//				return true;
//			}
//		}

//		fetchError(sqlQuery.lastError(), status);
//		return false;
//}

// template <typename Obj>
// void LocalManagement<Obj>::fetchError(const QSqlError &sqlErr, DBDB::StatusType *status) const
//{
//	switch(sqlErr.type()) {
//	case QSqlError::NoError:
//		*status = DBStatus::OK;
//		break;

//	case QSqlError::ConnectionError:
//		*status = DBStatus::ERR_DATABASE_INTERNAL;
//		break;

//	case QSqlError::StatementError:
//		std::runtime_error("Error syntax SQL Local Database");
//		*status = DBStatus::ERR_DATABASE_SYNTAX;
//		break;

//	case QSqlError::TransactionError:
//		*status = DBStatus::ERR_DATABASE_INTERNAL;
//		break;

//	case QSqlError::UnknownError:
//		*status = DBStatus::ERR_DATABASE_INTERNAL;
//		break;
//	}
//}

#include "LocalManagement.h"

namespace DB
{
	LocalManagement::LocalManagement(const QSqlDatabase &database)
		: m_database(database)
	{
		if(!m_database.isOpen()) {
			if(!m_database.open()) {
				fetchError(m_database.lastError());
			}
		}
	}

	LocalManagement::~LocalManagement()
	{
	}

	QSqlRecord LocalManagement::getRecord(const DB::Query &query, DB::Status *status) const
	{
		QString sql(query.query.c_str());
		QSqlQuery sqlQuery(m_database);

		if(sqlQuery.prepare(sql)) {
			if(sqlQuery.exec()) {
				fetchError(sqlQuery.lastError(), status);
				if(sqlQuery.next()) {
					return sqlQuery.record();
				} else {
					return QSqlRecord();
				}
			}
		}

		fetchError(sqlQuery.lastError(), status);
		return QSqlRecord();
	}

	std::vector<QSqlRecord> LocalManagement::getRecords(const DB::Query &query, DB::Status *status) const
	{
		QString sql(query.query.c_str());
		QSqlQuery sqlQuery(m_database);

		if(sqlQuery.prepare(sql)) {
			if(sqlQuery.exec()) {
				std::vector<QSqlRecord> objs;
				while(sqlQuery.next()) {
					objs.push_back(sqlQuery.record());
				}
				fetchError(sqlQuery.lastError(), status);
				return objs;
			}
		}

		fetchError(sqlQuery.lastError(), status);
		return {};
	}

	bool LocalManagement::execQuery(const DB::Query &query, DB::Status *status) const
	{
		QString sql(query.query.c_str());
		QSqlQuery sqlQuery(m_database);

		if(sqlQuery.prepare(sql)) {
			if(sqlQuery.exec()) {
				fetchError(sqlQuery.lastError(), status);
				return true;
			}
		}

		fetchError(sqlQuery.lastError(), status);
		return false;
	}

	void LocalManagement::fetchError(const QSqlError &sqlErr, DB::Status *status) const
	{
		switch(sqlErr.type()) {
		case QSqlError::NoError:
			if(status) {
				*status = Status::OK;
			}
			break;

		case QSqlError::ConnectionError:
			qDebug() << "Error INTERNAL DATABASE";
			if(status) {
				*status = Status::ERR_DATABASE_INTERNAL;
			}
			break;

		case QSqlError::StatementError:
			qDebug() << "Error syntax SQL Local Database";
			//		std::runtime_error("Error syntax SQL Local Database");
			if(status) {
				*status = Status::ERR_DATABASE_SYNTAX;
			}
			break;

		case QSqlError::TransactionError:
			qDebug() << "Error interal DB (transaction).";
			if(status) {
				*status = Status::ERR_DATABASE_INTERNAL;
			}
			break;

		case QSqlError::UnknownError:
		default:
			qDebug() << "Error internal DB (unknown)";
			if(status) {
				*status = Status::ERR_DATABASE_INTERNAL;
			}
			break;
		}
	}
}

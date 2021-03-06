#include "SqlLocalManagement.h"

SqlLocalManagement::SqlLocalManagement(const QSqlDatabase &database)
	: m_database(database)
{
	if(!m_database.isOpen()) {
		if(!m_database.open()) {
			fetchError(m_database.lastError());
		}
	}
}

QSqlRecord SqlLocalManagement::getRecord(const Query &query, DBStatus::StatusType *status) const
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

std::vector<QSqlRecord> SqlLocalManagement::getRecords(const Query &query, DBStatus::StatusType *status) const
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

bool SqlLocalManagement::execQuery(const Query &query, DBStatus::StatusType *status) const
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

void SqlLocalManagement::fetchError(const QSqlError &sqlErr, DBStatus::StatusType *status) const
{
	switch(sqlErr.type()) {
	case QSqlError::NoError:
		if(status) {
			*status = DBStatus::OK;
		}
		break;

	case QSqlError::ConnectionError:
		qDebug() << "Error INTERNAL DATABASE";
		if(status) {
			*status = DBStatus::ERR_DATABASE_INTERNAL;
		}
		break;

	case QSqlError::StatementError:
		qDebug() << "Error syntax SQL Local Database";
		//		std::runtime_error("Error syntax SQL Local Database");
		if(status) {
			*status = DBStatus::ERR_DATABASE_SYNTAX;
		}
		break;

	case QSqlError::TransactionError:
		qDebug() << "Error interal DB (transaction).";
		if(status) {
			*status = DBStatus::ERR_DATABASE_INTERNAL;
		}
		break;

	case QSqlError::UnknownError:
	default:
		qDebug() << "Error internal DB (unknown)";
		if(status) {
			*status = DBStatus::ERR_DATABASE_INTERNAL;
		}
		break;
	}
}

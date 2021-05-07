#include "WebDatabaseManager.h"

WebDatabaseManager::WebDatabaseManager(const QString &domain_)
	: domain(domain_)
{
	connectUser();
	m_networkManager = std::make_unique<QNetworkAccessManager>();
}

WebDatabaseManager::~WebDatabaseManager()
{
	m_networkManager.reset();
}

void WebDatabaseManager::connectUser()
{
	m_body = QString("m_log=%1&m_pass=%2&m_type=").arg(UserSession::getInstance().getUser().login, UserSession::getInstance().getUser().password);
}

QJsonObject WebDatabaseManager::get(const QString &request, DBStatus::StatusType *status)
{
	connectUser();

	m_request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
	m_request.setUrl(QUrl(domain + request));

	m_reply = m_networkManager->post(m_request, QString(m_body + "GET").toUtf8());

	QEventLoop loop;
	connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();

	QJsonObject jsonReply;
	QString replyString = "";
	QJsonParseError jsonParseErr;


	if(m_reply->error() == QNetworkReply::NoError) {
		if(m_reply->bytesAvailable()) {
			replyString = m_reply->readAll();

//			qDebug() << "ODP z GET: " << replyString;

			for(auto statusIt = DBStatus::statuses.begin(); statusIt != DBStatus::statuses.end(); ++statusIt) {
				if(replyString.contains(statusIt->second.c_str())) {
					*status = statusIt->first;
					break;
				}else {
					*status = DBStatus::OK;
				}
			}

			QJsonDocument jsonDoc = QJsonDocument::fromJson(replyString.toUtf8(), &jsonParseErr);
			jsonReply = jsonDoc.object();

			if(jsonParseErr.error != 0) {
				qDebug() << "ERROR DURING PARSE JSON FROM WebDB: " << jsonParseErr.error <<  " = " << jsonParseErr.errorString();
			}
		}
	}else if(m_reply->error() == QNetworkReply::UnknownNetworkError || m_reply->error() == QNetworkReply::HostNotFoundError) {
		*status = DBStatus::ERR_NETWORK_NOT_CONNECTED;
	}else {
		*status = DBStatus::ERR_UNKNOWN;
		qDebug() << "ERROR DURING GET: " << m_reply->error() << " = " << m_reply->errorString();
	}

	return jsonReply;
}

QJsonObject WebDatabaseManager::put(const QString &request, const QString &body, DBStatus::StatusType *status)
{
	connectUser();

	m_request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
	m_request.setUrl(QUrl(domain + request));

	m_reply = m_networkManager->post(m_request, QString(m_body + "PUT&m_body=" + body).toUtf8());

	QEventLoop loop;
	connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();

	QJsonObject jsonReply;
	QString replyString = "";
	QJsonParseError jsonParseErr;


	if(m_reply->error() == QNetworkReply::NoError) {
		if(m_reply->bytesAvailable()) {
			replyString = m_reply->readAll();

			qDebug() << "ODP z PUT: " << replyString;

			for(auto statusIt = DBStatus::statuses.begin(); statusIt != DBStatus::statuses.end(); ++statusIt) {
				if(replyString.contains(statusIt->second.c_str())) {
					*status = statusIt->first;
					break;
				}else {
					*status = DBStatus::OK;
				}
			}

			QJsonDocument jsonDoc = QJsonDocument::fromJson(replyString.toUtf8(), &jsonParseErr);
			jsonReply = jsonDoc.object();

			if(jsonParseErr.error != 0) {
				qDebug() << "ERROR DURING PARSE JSON FROM WebDB: " << jsonParseErr.error <<  " = " << jsonParseErr.errorString();
			}
		}
	}else if(m_reply->error() == QNetworkReply::UnknownNetworkError || m_reply->error() == QNetworkReply::HostNotFoundError) {
		*status = DBStatus::ERR_NETWORK_NOT_CONNECTED;
	}else {
		*status = DBStatus::ERR_UNKNOWN;
		qDebug() << "ERROR DURING PUT: " << m_reply->error() << " = " << m_reply->errorString();
		qDebug() << "URL: " << domain + request;
		qDebug() << "BODY: " << QString(m_body + "PUT&m_body=" + body);
	}

	return jsonReply;
}


QJsonObject WebDatabaseManager::post(const QString &request, const QString &body, DBStatus::StatusType *status)
{
	connectUser();

	m_request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
	m_request.setUrl(QUrl(domain + request));

	m_reply = m_networkManager->post(m_request, QString(m_body + "POST&m_body=" + body).toUtf8());

	QEventLoop loop;
	connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();

	QJsonObject jsonReply;
	QString replyString = "";
	QJsonParseError jsonParseErr;

	if(m_reply->error() == QNetworkReply::NoError) {
		if(m_reply->bytesAvailable()) {
			replyString = m_reply->readAll();

			qDebug() << "ODP z POST: " << replyString;

			for(auto statusIt = DBStatus::statuses.begin(); statusIt != DBStatus::statuses.end(); ++statusIt) {
				if(replyString.contains(statusIt->second.c_str())) {
					*status = statusIt->first;
					break;
				}else {
					*status = DBStatus::OK;
				}
			}

			QJsonDocument jsonDoc = QJsonDocument::fromJson(replyString.toUtf8(), &jsonParseErr);
			jsonReply = jsonDoc.object();

			if(jsonParseErr.error != 0) {
				qDebug() << "ERROR DURING PARSE JSON FROM WebDB: " << jsonParseErr.error <<  " = " << jsonParseErr.errorString();
			}
		}
	}else if(m_reply->error() == QNetworkReply::UnknownNetworkError || m_reply->error() == QNetworkReply::HostNotFoundError) {
		*status = DBStatus::ERR_NETWORK_NOT_CONNECTED;
	}else {
		*status = DBStatus::ERR_UNKNOWN;
		qDebug() << "ERROR DURING POST: " << m_reply->error() << " = " << m_reply->errorString();
		qDebug() << "URL: " << domain + request;
		qDebug() << "BODY: " << QString(m_body + "POST&m_body=" + body);
	}

	return jsonReply;
}

QJsonObject WebDatabaseManager::delete_(const QString &request, DBStatus::StatusType *status)
{
	connectUser();

	m_request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
	m_request.setUrl(QUrl(domain + request));

	m_reply = m_networkManager->post(m_request, QString(m_body + "DELETE").toUtf8());

	QEventLoop loop;
	connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();

	QJsonObject jsonReply;
	QString replyString = "";
	QJsonParseError jsonParseErr;


	if(m_reply->error() == QNetworkReply::NoError) {
		if(m_reply->bytesAvailable()) {
			replyString = m_reply->readAll();

//			qDebug() << "ODP z GET: " << replyString;

			for(auto statusIt = DBStatus::statuses.begin(); statusIt != DBStatus::statuses.end(); ++statusIt) {
				if(replyString.contains(statusIt->second.c_str())) {
					*status = statusIt->first;
					break;
				}else {
					*status = DBStatus::OK;
				}
			}

			QJsonDocument jsonDoc = QJsonDocument::fromJson(replyString.toUtf8(), &jsonParseErr);
			jsonReply = jsonDoc.object();

			if(jsonParseErr.error != 0) {
				qDebug() << "ERROR DURING PARSE JSON FROM WebDB: " << jsonParseErr.error <<  " = " << jsonParseErr.errorString();
			}
		}
	}else if(m_reply->error() == QNetworkReply::UnknownNetworkError || m_reply->error() == QNetworkReply::HostNotFoundError) {
		*status = DBStatus::ERR_NETWORK_NOT_CONNECTED;
	}else {
		*status = DBStatus::ERR_UNKNOWN;
		qDebug() << "ERROR DURING GET: " << m_reply->error() << " = " << m_reply->errorString();
	}

	return jsonReply;
}

#pragma once

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
#include <QObject>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

#include "Common/UserSession.h"
#include "Resources/DatabaseStatus.h"

class WebDatabaseManager : public QObject
{
	Q_OBJECT
public:
	WebDatabaseManager(const QString &domain_);
	~WebDatabaseManager();

	QJsonObject get(const QString &request, DBStatus::StatusType *status = nullptr);
	QJsonObject put(const QString &request, const QString &body, DBStatus::StatusType *status = nullptr);
	QJsonObject post(const QString &request, const QString &body, DBStatus::StatusType *status = nullptr);
	QJsonObject delete_(const QString &request, DBStatus::StatusType *status = nullptr);

	QString domain;

private:
	void connectUser();

	QNetworkRequest m_request;
	QNetworkReply *m_reply;
	QString m_body;

	std::unique_ptr<QNetworkAccessManager> m_networkManager;
};

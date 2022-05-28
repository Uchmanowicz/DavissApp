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

namespace DB
{
	class IWebDbExecutor : public QObject
	{
		Q_OBJECT
	public:
		IWebDbExecutor(const QString &domain_);
		virtual ~IWebDbExecutor();

		virtual QJsonObject get(const QString &request, DB::Status *status = nullptr) = 0;
		virtual QJsonObject put(const QString &request, const QString &body, DB::Status *status = nullptr) = 0;
		virtual QJsonObject post(const QString &request, const QString &body, DB::Status *status = nullptr) = 0;
		virtual QJsonObject delete_(const QString &request, DB::Status *status = nullptr) = 0;

		QString domain;

	protected:
		virtual void connectUser();

		QNetworkRequest m_request;
		QNetworkReply *m_reply;
		QString m_body;

		std::unique_ptr<QNetworkAccessManager> m_networkManager;
	};
}

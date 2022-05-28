#pragma once

#include "Common/UserSession.h"
#include "Resources/IWebDbExecutor.h"
#include "Resources/DatabaseStatus.h"

namespace DB
{
	class WebMySqlDbExecutor : public DB::IWebDbExecutor
	{
		Q_OBJECT
	public:
		WebMySqlDbExecutor(const QString &domain_);
		~WebMySqlDbExecutor() = default;

		QJsonObject get(const QString &request, DB::Status *status = nullptr) override;
		QJsonObject put(const QString &request, const QString &body, DB::Status *status = nullptr) override;
		QJsonObject post(const QString &request, const QString &body, DB::Status *status = nullptr) override;
		QJsonObject delete_(const QString &request, DB::Status *status = nullptr) override;

		QString domain;

	private:
		void connectUser() override;

		QNetworkRequest m_request;
		QNetworkReply *m_reply;
		QString m_body;

		std::unique_ptr<QNetworkAccessManager> m_networkManager;
	};
}

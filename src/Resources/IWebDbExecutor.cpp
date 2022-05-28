#include "IWebDbExecutor.h"

using namespace Person;
using namespace DB;

namespace DB
{
	IWebDbExecutor::IWebDbExecutor(const QString &domain_)
		: domain(domain_)
	{
		connectUser();
		m_networkManager = std::make_unique<QNetworkAccessManager>();
	}

	IWebDbExecutor::~IWebDbExecutor()
	{
		m_networkManager.reset();
	}

	void IWebDbExecutor::connectUser()
	{
		m_body = QString("m_log=%1&m_pass=%2&m_type=").arg(UserSession::getInstance().getUser().login, UserSession::getInstance().getUser().password);
	}
}

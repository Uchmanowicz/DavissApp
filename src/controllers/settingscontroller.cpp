#include "controllers/settingscontroller.h"

SettingsController::SettingsController(DatabaseController &_db, QObject *parent)
    : QObject(parent),
      db(_db),
      m_userName("NONE"), m_userEmail("NONE"), m_userPassword("NONE"),
      m_userIsUpdateDepoTable(true), m_qmlIsLoggingProgress(false)
{
    networkManager = new QNetworkAccessManager(this);
}

SettingsController::~SettingsController()
{
    networkManager->deleteLater();
}

void SettingsController::replySignIn()
{
    QString replyUserName = networkReply->readAll();

    qDebug() << "DEBUG: Reply form server: userName = " << replyUserName;

    if(replyUserName.contains("NONE") && replyUserName.length() < 5)
    {
        clearUserData();
        qmlSetUserName("NONE");
    }else
    {
        qmlSetUserName(replyUserName);
        setUserData();
    }

    qmlSetIsLoggingProgress(false);
}

void SettingsController::setUserData()
{
    db.setUserInDb(m_userEmail, m_userPassword, m_userName);
}

QString SettingsController::convertPasswordToHash(QString password)
{
    QString hashedPassword;

#ifdef PROTECTOR
    Protector protector;

     hashedPassword = protector.convertPasswordToHash(password);
#else
    hashedPassword = "testPassword";
#endif

    return hashedPassword;
}

void SettingsController::clearUserData()
{
    qmlSetUserName("NONE");
    m_userEmail = "NONE";
    m_userPassword = "NONE";
    m_userIsUpdateDepoTable = true;

    db.setUserInDb(m_userEmail, m_userPassword, m_userName);
}

void SettingsController::qmlSignIn(QString email, QString password)
{
    m_userEmail = email;
    m_userPassword = convertPasswordToHash(password);

    qmlSetIsLoggingProgress(true);

    networkReply = networkManager->get(QNetworkRequest(QUrl(QString("http://daviss.pl/login.php?login=%1&password=%2")
                                                            .arg(m_userEmail, m_userPassword))));
    connect(networkReply, &QNetworkReply::readyRead, this, &SettingsController::replySignIn);
}

void SettingsController::qmlSignOut()
{
    qmlSetUserName("NONE");
}

const QString &SettingsController::qmlGetUserName() const
{
    return m_userName;
}

void SettingsController::qmlSetUserName(const QString & userName)
{
//    if(m_userName == userName)
//    {
//        return;
//    }

    m_userName = userName;
    emit qmlUserNameChanged(m_userName);
}

bool SettingsController::qmlGetIsLoggingProgress() const
{
    return m_qmlIsLoggingProgress;
}

void SettingsController::qmlSetIsLoggingProgress(bool qmlIsLoggingProgress)
{
    if (m_qmlIsLoggingProgress == qmlIsLoggingProgress)
        return;

    m_qmlIsLoggingProgress = qmlIsLoggingProgress;
    emit qmlIsLoggingProgressChanged(m_qmlIsLoggingProgress);
}

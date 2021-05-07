#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QSqlError>
#include <QSqlQuery>

#include <QCryptographicHash>
#include <QMessageAuthenticationCode>

#include <QDebug>

#include <controllers/databasecontroller.h>

#ifdef PROTECTOR
    #include <protector.h>
#endif


class SettingsController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString qmlUserName READ qmlGetUserName WRITE qmlSetUserName NOTIFY qmlUserNameChanged);
    Q_PROPERTY(bool qmlIsLoggingProgress READ qmlGetIsLoggingProgress WRITE qmlSetIsLoggingProgress NOTIFY qmlIsLoggingProgressChanged);

public:
    explicit SettingsController(DatabaseController &_db, QObject *parent = nullptr);
    ~SettingsController();

    Q_INVOKABLE void qmlSignIn(QString email, QString password);
    Q_INVOKABLE void qmlSignOut();

    Q_INVOKABLE const QString & qmlGetUserName() const;

    bool qmlGetIsLoggingProgress() const;

public slots:
    void qmlSetUserName(const QString & userName);
    void qmlSetIsLoggingProgress(bool qmlIsLoggingProgress);

signals:
    void qmlUserNameChanged(QString userName);
    void qmlIsLoggingProgressChanged(bool qmlIsLoggingProgress);

private slots:
    void replySignIn();

private:
    QNetworkAccessManager * networkManager;
    QNetworkReply * networkReply;

    DatabaseController &db;

    QString m_userName;
    QString m_userEmail;
    QString m_userPassword;
    bool m_userIsUpdateDepoTable;
    bool m_qmlIsLoggingProgress;


    void clearUserData();
    void setUserData();

    QString convertPasswordToHash(QString password);

};

#endif // SETTINGSCONTROLLER_H

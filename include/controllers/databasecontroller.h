#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QStandardPaths>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QVariantMap>
#include <QVariantList>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

#include <controllers/depocontroller.h>




class DatabaseController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList qmlDepoCategoryList READ qmlGetDepoCategoryList WRITE qmlSetDepoCategoryList NOTIFY qmlDepoCategoryListChanged);
    Q_PROPERTY(QString databasePath READ qmlGetDbPath WRITE qmlSetDbPath NOTIFY qmlDbPathChanged);

public:
    explicit DatabaseController(QObject *parent = nullptr);
    ~DatabaseController();

    DepoController depoController;

    const QVariantList & qmlGetDepoCategoryList() const;

    void setUserInDb(QString userEmail, QString userPassword, QString userName);

    bool connectToDb();

    QString qmlGetDbPath() const;

public slots:

    void qmlSetDepoCategoryList(const QVariantList & _list);

    void reply();

    void qmlRefreshDepoDb();


    void qmlSetDbPath(QString qmlDbPath);

private:

    QSqlDatabase db;
    QNetworkAccessManager * networkManager;
    QNetworkReply * networkReply;

    void create();

    void creatTableInDb(QString qryText);
    void createTableDepot();
    void createTableUser();

    bool checkIfTableExist(QString tableName);

    void addDataToDb(QString insertQry, QString updateQry);
    void setAndUpdateDepoData(QVariantMap data);

    QList<QString> getList(QString queryText);
    QList<QString> getDepoCategory();


    bool checkWritableLocation(QStandardPaths::StandardLocation pathType);

    QVariantList m_lista2;

    QString m_databasePath;

signals:
    void qmlDepoCategoryListChanged();
    void qmlDbPathChanged(QString qmlDbPath);
};

#endif // DATABASECONTROLLER_H

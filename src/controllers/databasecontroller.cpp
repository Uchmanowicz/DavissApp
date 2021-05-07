#include "controllers/databasecontroller.h"

DatabaseController::DatabaseController(QObject *parent)
    : QObject(parent)
{
    connectToDb();

    networkManager = new QNetworkAccessManager(this);

    //networkReply = networkManager->get(QNetworkRequest(QUrl("http:///api.php/records/Depot/")));
    //connect(networkReply, &QNetworkReply::readyRead, this, &DatabaseController::reply);

    if(!checkIfTableExist("Depot"))
        createTableDepot();

    if(!checkIfTableExist("User"))
        createTableUser();
}

DatabaseController::~DatabaseController()
{
    db.close();
    networkManager->deleteLater();
}

void DatabaseController::reply()
{
    QString replyJsonString = networkReply->readAll();

    QJsonDocument replyJsonDoc = QJsonDocument::fromJson(replyJsonString.toUtf8());
    QJsonObject replyJsonObject = replyJsonDoc.object();
    QVariantMap mainMap = replyJsonObject.toVariantMap();
    QVariantList localList = mainMap["records"].toList();
    QVariantMap map;

    for(int i = 0; i < localList.count(); i++)
    {
        map = localList[i].toMap();
        //setAndUpdateDepoData(map);
    }


    //m_lista2 = getDepoCategory();

}

void DatabaseController::createTableDepot()
{
    QString qryText = QString("CREATE TABLE Depot ("
                                      "ID INTEGER PRIMARY KEY,"
                                      "Category TEXT NULL DEFAULT NULL,"
                                      "SubCategory1 TEXT NULL DEFAULT NULL,"
                                      "SubCategory2 TEXT NULL DEFAULT NULL,"
                                      "SubCategory3 TEXT NULL DEFAULT NULL,"
                                      "SubCategory4 TEXT NULL DEFAULT NULL,"
                                      "SubCategory5 TEXT NULL DEFAULT NULL,"
                                      "SubCategory6 TEXT NULL DEFAULT NULL,"
                                      "Name TEXT NULL DEFAULT NULL,"
                                      "SerialName TEXT NULL DEFAULT NULL,"
                                      "Manufacturer TEXT NULL DEFAULT NULL,"
                                      "Quantity TEXT NULL DEFAULT NULL,"
                                      "Unit TEXT NULL DEFAULT NULL,"
                                      "Packaging TEXT NULL DEFAULT NULL,"
                                      "UsesOf TEXT NULL DEFAULT NULL,"
                                      "Power TEXT NULL DEFAULT NULL,"
                                      "Voltage TEXT NULL DEFAULT NULL,"
                                      "Ampere TEXT NULL DEFAULT NULL,"
                                      "Resistance TEXT NULL DEFAULT NULL,"
                                      "tdo1 TEXT NULL DEFAULT NULL,"
                                      "tdo2 TEXT NULL DEFAULT NULL,"
                                      "tdo3 TEXT NULL DEFAULT NULL,"
                                      "tdo4 TEXT NULL DEFAULT NULL,"
                                      "tdo5 TEXT NULL DEFAULT NULL);");

    creatTableInDb(qryText);
}

void DatabaseController::createTableUser()
{
    QString qryText = QString("CREATE TABLE User ("
                                      "ID INTEGER PRIMARY KEY,"
                                      "Name TEXT,"
                                      "Email TEXT,"
                                      "Password TEXT,"
                                      "TableDepoUpdate BOOLEAN NULL DEFAULT 1);");

    creatTableInDb(qryText);
}

void DatabaseController::creatTableInDb(QString qryText)
{
    QSqlQuery query(db);

    query.prepare(qryText);
    bool queryStatus = query.exec();

    if(!queryStatus)
        qDebug() << "Błąd utworzenia tabeli!" << query.lastError();

    query.finish();
}


bool DatabaseController::checkIfTableExist(QString tableName)
{
    bool isTableExists = db.tables().contains(tableName);

    return isTableExists;
}

void DatabaseController::addDataToDb(QString insertQry, QString updateQry)
{
    QSqlQuery query(db);

    query.prepare(insertQry);
    bool queryStatus = query.exec();

    if(!queryStatus)
        qDebug() << "Błąd dodani danych do tabeli1!: " << query.lastError();

    query.finish();

    query.prepare(updateQry);
    queryStatus = query.exec();

    if(!queryStatus)
        qDebug() << "Błąd zaktualizowania danych do tabeli!: " << query.lastError();

    query.finish();

}

void DatabaseController::setAndUpdateDepoData(QVariantMap data)
{
    QString insertQry = QString("INSERT OR IGNORE INTO Depot (Category, SubCategory1, SubCategory2, "
                                        "SubCategory3, SubCategory4, SubCategory5, "
                                        "SubCategory6, Name, SerialName, "
                                        "Manufacturer, Quantity, Unit, "
                                        "Packaging, UsesOf, Power, "
                                        "Voltage, Ampere, Resistance, "
                                        "tdo1, tdo2, tdo3, "
                                        "tdo4, tdo5) "
                                        "VALUES ('%1','%2','%3',"
                                        "'%4','%5','%6',"
                                        "'%7','%8','%9',"
                                        "'%10','%11','%12',"
                                        "'%13','%14','%15',"
                                        "'%16','%17','%18',"
                                        "'%19','%20','%21',"
                                        "'%22','%23');").arg(
                data["Category"].toString(), data["SubCategory1"].toString(), data["SubCategory2"].toString(),
            data["SubCategory3"].toString(), data["SubCategory4"].toString(), data["SubCategory5"].toString(),
            data["SubCategory6"].toString(), data["Name"].toString(), data["SerialName"].toString()).arg(
                data["Manufacturer"].toString(), data["Quantity"].toString(), data["Unit"].toString(),
            data["Packaging"].toString(), data["UsesOf"].toString(), data["Power"].toString()).arg(
                data["Voltage"].toString(), data["Ampere"].toString(), data["Resistance"].toString(),
            data["tdo1"].toString(), data["tdo2"].toString(), data["tdo3"].toString(),
            data["tdo4"].toString(), data["tdo5"].toString());


    QString updateQry = QString("UPDATE BasicTable "
                                        "SET CurrentLanguage = '%1'"
                                        "WHERE ID = '1';").arg("language");

    addDataToDb(insertQry, updateQry);
}

bool DatabaseController::checkWritableLocation(QStandardPaths::StandardLocation pathType)
{
    bool status;
    QString pathStatus = QStandardPaths::writableLocation(pathType);

    if(!pathStatus.isEmpty() && pathStatus.length() > 2)
    {
        status = true;
    }
    else
    {
        status = false;
    }


    return status;
}

bool DatabaseController::connectToDb()
{

    QString tempDbPath;

#if defined(Q_OS_ANDROID)

    if(checkWritableLocation(QStandardPaths::DataLocation))
    {
        tempDbPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    }else if(checkWritableLocation(QStandardPaths::DocumentsLocation))
    {
        tempDbPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    }else if(checkWritableLocation(QStandardPaths::DownloadLocation))
    {
        tempDbPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

    }else
    {
        tempDbPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    }
#elif defined(Q_OS_WINDOWS)
    if(checkWritableLocation(QStandardPaths::DataLocation))
    {
        tempDbPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    }else if(checkWritableLocation(QStandardPaths::DocumentsLocation))
    {
        tempDbPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    }else if(checkWritableLocation(QStandardPaths::DownloadLocation))
    {
        tempDbPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

    }else
    {
        tempDbPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    }

#endif

    tempDbPath = QString("%1/dbDaviss.db").arg(tempDbPath);

    qmlSetDbPath(tempDbPath);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(m_databasePath);
    db.database(m_databasePath);

    bool dbStatus = db.open();

    if(dbStatus)
    {
        qDebug() << "DEBUG: Connected to database.\n\tDIR = " << m_databasePath;
        return true;
    }else
    {
        qDebug() << "DEBUG: Error: No connection to database.\n\tDescription: " << db.lastError();
        return false;
    }
}

QString DatabaseController::qmlGetDbPath() const
{
    return m_databasePath;
}

QList<QString> DatabaseController::getList(QString queryText)
{
    QSqlQuery query(db);

    query.prepare(queryText);
    bool queryStatus = query.exec();

    if(!queryStatus)
        qDebug() << "Błąd pobrania danych z tabeli1!: " << query.lastError();

    QList<QString> retList;

    while(query.next())
        retList << query.value(0).toString();



    query.finish();

    return retList;
}

QList<QString> DatabaseController::getDepoCategory()
{
    QString qryText = QString("SELECT DISTINCT Category FROM Depot");

    QList<QString> categoryList = getList(qryText);

    categoryList.sort(Qt::CaseInsensitive);

    return categoryList;
}



void DatabaseController::qmlRefreshDepoDb()
{
    QList<QString> te;
    te = getDepoCategory();
    QVariantList test;

    for(QString x : te)
    {
        test << x;
    }

    qmlSetDepoCategoryList(test);
}

void DatabaseController::qmlSetDbPath(QString dbPath)
{
    if (m_databasePath == dbPath)
        return;

    m_databasePath = dbPath;
    emit qmlDbPathChanged(m_databasePath);
}















const QVariantList & DatabaseController::qmlGetDepoCategoryList() const
{
    return m_lista2;
}

void DatabaseController::setUserInDb(QString userEmail, QString userPassword, QString userName)
{
    QString insertQry = QString("INSERT OR IGNORE INTO User (ID, Name, Email, Password) "
                                        "VALUES ('%1','%2','%3', '%4');").arg(
                "1", userName, userEmail, userPassword);


    QString updateQry = QString("UPDATE User "
                                        "SET Name = '%1', Email = '%2', Password = '%3'"
                                        "WHERE ID = '1';").arg(
                userName, userEmail, userPassword);

    addDataToDb(insertQry, updateQry);
}

void DatabaseController::qmlSetDepoCategoryList(const QVariantList & alist)
{
    if(m_lista2 == alist)
    {
        return;
    }
    m_lista2 = alist;
    emit qmlDepoCategoryListChanged();
}

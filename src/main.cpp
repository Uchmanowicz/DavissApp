#include "Application.h"

#include <QDebug>

//void setUpAppCore(QGuiApplication & app)
//{
//#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif


//    app.setWindowIcon(QIcon("qrc:/resources/logo/icon.ico"));

//}

//void setUpAppUI(QGuiApplication & app, QQmlApplicationEngine & qmlEngine, MvcAdapter & MVC)
//{
//    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
//    QObject::connect(&qmlEngine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);


//    bool OS_ANDROID, OS_WINDOWS = false;

//#if defined(Q_OS_ANDROID)
//    OS_ANDROID = true;
//    OS_WINDOWS = false;
//#elif defined(Q_OS_WINDOWS)
//    OS_ANDROID = false;
//    OS_WINDOWS = true;
//#else
//    OS_ANDROID = false;
//    OS_WINDOWS = false;
//#endif

//    qmlEngine.rootContext()->setContextProperty("OS_ANDROID", QVariant(OS_ANDROID));
//    qmlEngine.rootContext()->setContextProperty("OS_WINDOWS", QVariant(OS_WINDOWS));

//    qmlEngine.rootContext()->setContextProperty("MVC", & MVC);

//    qmlEngine.load(url);
//}




int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

		Application app(argc, argv);
		app.init();

//	app.setWindowIcon(QIcon("qrc:/resources/logo/icon.ico"));


//    QGuiApplication app(argc, argv);

//    setUpAppCore(app);

//    Domain domain;

//    SQLiteAdapter internalDb;
//    MySqlAdapter externalDb;

//    ApplicationLogic applicationLogic(domain, internalDb, externalDb);

//    MvcAdapter MVC(applicationLogic);

//    QQmlApplicationEngine qmlEngine;
//    setUpAppUI(app, qmlEngine, MVC);

		//int result = app.exec();
		return  app.exec();//result;
}

#ifndef DEPOCONTROLLER_H
#define DEPOCONTROLLER_H

#include <QObject>
#include <QStandardItemModel>

#include <QDebug>


class TreeViewModel : public QStandardItemModel
{
    Q_OBJECT
public:
    TreeViewModel(QObject * parent = nullptr);
    ~TreeViewModel();

};



class DepoController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString qmlDepoCategoryName READ qmlGetDepoCategoryName WRITE qmlSetDepoCategoryName NOTIFY qmlDepoCategoryNameChanged);
    Q_PROPERTY(QString qmlDepoSub1CatName READ qmlGetDepoSub1CatName WRITE qmlSetDepoSub1CatName NOTIFY qmlDepoSub1CatNameChanged);

public:
    explicit DepoController(QObject *parent = nullptr);
    ~DepoController();

    TreeViewModel treeViewModel;

    QString qmlGetDepoCategoryName();
    QString qmlGetDepoSub1CatName();

public slots:
    void qmlSetDepoCategoryName(QString categoryName);
    void qmlSetDepoSub1CatName(QString categoryName);

    void qmlClearAllFilteres();

signals:
    void qmlDepoCategoryNameChanged(QString categoryName);
    void qmlDepoSub1CatNameChanged(QString subCategoryName);

private:
    QString m_categoryName;
    QString m_sub1CategoryName;



};





#endif // DEPOCONTROLLER_H

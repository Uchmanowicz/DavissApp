#include "controllers/depocontroller.h"

DepoController::DepoController(QObject *parent)
    : QObject(parent),
      m_categoryName("NONE"),
      m_sub1CategoryName("NONE")
{

}

DepoController::~DepoController()
{

}

QString DepoController::qmlGetDepoCategoryName()
{
    return m_categoryName;
}

QString DepoController::qmlGetDepoSub1CatName()
{
    return m_categoryName;
}

void DepoController::qmlSetDepoCategoryName(QString categoryName)
{

    if(m_categoryName == categoryName)
    {
        return;
    }
    qDebug() << "Zmieniam Categorie z " << m_categoryName << " na: " << categoryName;
    m_categoryName = categoryName;
    emit qmlDepoCategoryNameChanged(m_categoryName);
}

void DepoController::qmlSetDepoSub1CatName(QString subCategoryName)
{

    if(m_sub1CategoryName == subCategoryName)
    {
        return;
    }
    qDebug() << "Zmieniam Sub1Category z " << m_sub1CategoryName << " na: " << subCategoryName;
    m_sub1CategoryName = subCategoryName;
    emit qmlDepoCategoryNameChanged(m_sub1CategoryName);
}

void DepoController::qmlClearAllFilteres()
{
    m_categoryName = "NONE";
    m_sub1CategoryName = "NONE";
}












TreeViewModel::TreeViewModel(QObject *parent)
    : QStandardItemModel{parent}
{

    setColumnCount(2);

    QStandardItem * rootItem = invisibleRootItem();


    QStandardItem * gr3 = new QStandardItem;



    QStandardItem * val1 = new QStandardItem;
    QStandardItem * val2 = new QStandardItem;
    QStandardItem * val3 = new QStandardItem;
    QStandardItem * val4 = new QStandardItem;
    QStandardItem * val5 = new QStandardItem;



    val1->setText("val1");
    val2->setText("val2");
    val3->setText("val3");
    val4->setText("val4");
    val5->setText("val5");

    QList<QStandardItem *> gr1 = {val1, val2};
    QList<QStandardItem *> gr2 = {val3, val4};
    gr3->setText("GR3");

   // gr1->appendRow(gr3);

    //gr3->appendRow(val1);
    //gr3->appendRow(val2);

//    gr2->appendRow(val3);
//    gr2->appendRow(val4);
//    gr2->appendRow(val5);

        rootItem->appendRow(gr1);
        rootItem->appendRow(gr2);

//    QList<QStandardItem *> list;

//    list << gr1 << gr3;

//    rootItem->appendRow(list);
//    rootItem->appendRow(gr2);

//    QStandardItem * col1 = new QStandardItem;
//    QStandardItem * col2 = new QStandardItem;

//    col1->setText("cat1");
//    col2->setText("cat2");

//    QList<QStandardItem *> test;

//    test << gr2 << gr1 ;

//    rootItem->appendColumn(test);/*==*/
}

TreeViewModel::~TreeViewModel()
{

}

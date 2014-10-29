#ifndef TESTSESSIONMODEL_H
#define TESTSESSIONMODEL_H

#include <QtTest>
#include "SessionModel.h"
#include "SampleModel.h"
#include "MaterialModel.h"
#include "InstrumentModel.h"
#include "MaterialEditor.h"
#include <QXmlStreamWriter>

class TestSessionModel : public QObject {
    Q_OBJECT

private slots:
    void test_SampleModel_CreateCopy();
    void test_SampleModel_CreatePartialCopy();
    void test_InstrumentModel_CreateCopy();
    void test_InstrumentModel_CreatePartialCopy();
};


inline void TestSessionModel::test_SampleModel_CreateCopy()
{
    boost::scoped_ptr<MaterialModel> materialModel(new MaterialModel());
    boost::scoped_ptr<MaterialEditor> materialEditor(new MaterialEditor(materialModel.get()));

    SampleModel *model1 = new SampleModel();
    ParameterizedItem *multilayer = model1->insertNewItem(Constants::MultiLayerType);
    multilayer->setItemName("multilayer");
    model1->insertNewItem(Constants::LayerType, model1->indexOfItem(multilayer));
    ParameterizedItem *multilayer2 = model1->insertNewItem(Constants::MultiLayerType);
    multilayer2->setItemName("multilayer2");

    QString buffer1;
    QXmlStreamWriter writer1(&buffer1);
    model1->writeTo(&writer1);

    SampleModel *model2 = model1->createCopy();
    QString buffer2;
    QXmlStreamWriter writer2(&buffer2);
    model2->writeTo(&writer2);

    QCOMPARE(buffer1, buffer2);

    delete model1;
    delete model2;
}


inline void TestSessionModel::test_SampleModel_CreatePartialCopy()
{
    boost::scoped_ptr<MaterialModel> materialModel(new MaterialModel());
    boost::scoped_ptr<MaterialEditor> materialEditor(new MaterialEditor(materialModel.get()));

    SampleModel *model1 = new SampleModel();
    ParameterizedItem *multilayer1 = model1->insertNewItem(Constants::MultiLayerType);
    multilayer1->setItemName("multilayer1");
    model1->insertNewItem(Constants::LayerType, model1->indexOfItem(multilayer1));

    ParameterizedItem *multilayer2 = model1->insertNewItem(Constants::MultiLayerType);
    multilayer2->setItemName("multilayer2");

    SampleModel *model2 = model1->createCopy(multilayer1);
    ParameterizedItem *result = model2->itemForIndex(model2->index(0,0,QModelIndex()));

    QCOMPARE(result->itemName(), multilayer1->itemName());
    QCOMPARE(result->modelType(), multilayer1->modelType());

    delete model1;
    delete model2;
}


inline void TestSessionModel::test_InstrumentModel_CreateCopy()
{
    InstrumentModel *model1 = new InstrumentModel();
    ParameterizedItem *instrument1 = model1->insertNewItem(Constants::InstrumentType);
    instrument1->setItemName("instrument1");
    model1->insertNewItem(Constants::DetectorType, model1->indexOfItem(instrument1));
    model1->insertNewItem(Constants::BeamType, model1->indexOfItem(instrument1));

    ParameterizedItem *instrument2 = model1->insertNewItem(Constants::InstrumentType);
    instrument2->setItemName("instrument2");
    model1->insertNewItem(Constants::DetectorType, model1->indexOfItem(instrument2));
    model1->insertNewItem(Constants::BeamType, model1->indexOfItem(instrument2));

    QString buffer1;
    QXmlStreamWriter writer1(&buffer1);
    model1->writeTo(&writer1);

    InstrumentModel *model2 = model1->createCopy();
    QString buffer2;
    QXmlStreamWriter writer2(&buffer2);
    model2->writeTo(&writer2);

    QCOMPARE(buffer1, buffer2);

    delete model1;
    delete model2;
}


inline void TestSessionModel::test_InstrumentModel_CreatePartialCopy()
{
    InstrumentModel *model1 = new InstrumentModel();
    ParameterizedItem *instrument1 = model1->insertNewItem(Constants::InstrumentType);
    instrument1->setItemName("instrument1");
    model1->insertNewItem(Constants::DetectorType, model1->indexOfItem(instrument1));
    model1->insertNewItem(Constants::BeamType, model1->indexOfItem(instrument1));

    ParameterizedItem *instrument2 = model1->insertNewItem(Constants::InstrumentType);
    instrument2->setItemName("instrument2");
    model1->insertNewItem(Constants::DetectorType, model1->indexOfItem(instrument2));
    model1->insertNewItem(Constants::BeamType, model1->indexOfItem(instrument2));

    InstrumentModel *model2 = model1->createCopy(instrument2);

    ParameterizedItem *result = model2->itemForIndex(model2->index(0,0,QModelIndex()));

    QCOMPARE(result->itemName(), instrument2->itemName());
    QCOMPARE(result->modelType(), instrument2->modelType());

    delete model1;
    delete model2;
}



#endif


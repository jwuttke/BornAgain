#include "GUIExamplesFactory.h"
#include "GUIObjectBuilder.h"
#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "GUIHelpers.h"
#include <QDebug>

//! Defines correspondance between example name and real name of simulation from SimulationRegistry
QMap<QString, QString > init_NameToRegistry()
{
    QMap<QString, QString > result;
    result["example01"] = "isgisaxs01";
    result["example02"] = "isgisaxs04_1DDL";
    result["example03"] = "isgisaxs04_2DDL";
    result["example04"] = "isgisaxs11";
    result["example05"] = "LayerWithRoughness";
    return result;
}

QMap<QString, QString> GUIExamplesFactory::m_name_to_registry = init_NameToRegistry();

bool GUIExamplesFactory::isValidExampleName(const QString &name)
{
    return m_name_to_registry.contains(name);
}


ParameterizedItem *GUIExamplesFactory::createSampleItems(const QString &name, SampleModel *sampleModel)
{
    if(sampleModel->getModelTag() != SessionXML::SampleModelTag ) {
        throw GUIHelpers::Error("GUIExamplesFactory::createSampleItems() -> Error. Not a SampleModelTag");
    }

    QString exampleName = m_name_to_registry[name];

    SampleBuilderFactory factory;
    boost::scoped_ptr<ISample> sample(factory.createSample(exampleName.toAscii().data()));

    Q_ASSERT(sample.get());
    sample->setName(name.toUtf8().constData());
    sample->printSampleTree();

    GUIObjectBuilder guiBuilder;
    return guiBuilder.populateSampleModel(sampleModel, sample.get());
    //return guiBuilder.getTopItem();
}

ParameterizedItem *GUIExamplesFactory::createInstrumentItems(const QString &name, InstrumentModel *instrumentModel)
{
    if(instrumentModel->getModelTag() != SessionXML::InstrumentModelTag ) {
        throw GUIHelpers::Error("GUIExamplesFactory::createInstrumentItems() -> Error. Not an InstrumentModelTag");
    }

    QString exampleName = m_name_to_registry[name];

    SimulationRegistry registry;
    boost::scoped_ptr<Simulation> simulation(registry.createItem(exampleName.toAscii().data()));
    Q_ASSERT(simulation.get());

    boost::scoped_ptr<Instrument> instrument(new Instrument(simulation.get()->getInstrument()));
    QString instrumentName = name + "_instrument";
    instrument->setName(instrumentName.toUtf8().constData());

    //simulation->setName(name.toUtf8().constData());
    qDebug() << " ";
    qDebug() << " GUIExamplesFactory::createInstrumentItems()";

    GUIObjectBuilder guiBuilder;
    return guiBuilder.populateInstrumentModel(instrumentModel, instrument.get());
}

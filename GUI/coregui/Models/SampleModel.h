#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include "SessionModel.h"
#include "MaterialProperty.h"
#include <QStringList>

class BA_CORE_API_ SampleModel : public SessionModel
{
    Q_OBJECT

public:
    explicit SampleModel(QObject *parent = 0);
    ~SampleModel(){}

    SampleModel *createCopy(ParameterizedItem *parent = 0);

    QMap<QString, ParameterizedItem *> getSampleMap() const;

public slots:
    void onMaterialModelChanged(const QModelIndex &first, const QModelIndex &second);

private:
    void exploreForMaterials(const QModelIndex &parentIndex = QModelIndex());
    QString m_material_identifier;
};




#endif

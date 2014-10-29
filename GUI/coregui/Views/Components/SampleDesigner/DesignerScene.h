#ifndef DESIGNERSCENE_H
#define DESIGNERSCENE_H

#include "WinDllMacros.h"
#include <QGraphicsScene>
#include <QModelIndex>
#include <QMap>

class InstrumentModel;
class SampleModel;
class ParameterizedItem;
class ParameterizedGraphicsItem;
class QItemSelectionModel;
class IView;
class QItemSelection;
class NodeEditorConnection;
class DesignerMimeData;
class SampleViewAligner;
class NodeEditor;


//! Main class which represents SessionModel on graphics scene
class BA_CORE_API_ DesignerScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit DesignerScene(QObject *parent = 0);
    virtual ~DesignerScene();

    void setSampleModel(SampleModel *sampleModel);
    void setInstrumentModel(InstrumentModel *instrumentModel);
    void setSelectionModel(QItemSelectionModel *model);

    SampleModel *getSampleModel() { return m_sampleModel; }

    IView *getViewForItem(ParameterizedItem *item) { return m_ItemToView[item]; }

    NodeEditor *getNodeEditor() { return m_nodeEditor;}

signals:
    void selectionModeChangeRequest(int);

public slots:
    void onSceneSelectionChanged();
    void onSessionSelectionChanged(const QItemSelection &, const QItemSelection &);
    void resetScene();
    void updateScene();

    void onRowsInserted(const QModelIndex &parent, int first, int last);
    void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);

    void setLayerInterfaceLine(const QLineF &line=QLineF()) { m_layer_interface_line = line; }

    void deleteSelectedItems();

    void onEstablishedConnection(NodeEditorConnection *); // to process signals from NodeEditor
    void removeConnection(NodeEditorConnection *);

    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void onSmartAlign();


protected:
    void drawForeground(QPainter* painter, const QRectF& rect);
    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);

private:

    IView *addViewForItem(ParameterizedItem *item);
    void updateViews(const QModelIndex &parentIndex = QModelIndex(), IView *parentView = 0);
    void deleteViews(const QModelIndex & parentIndex);
    void alignViews();
    void removeItemViewFromScene(ParameterizedItem *item);
    bool isMultiLayerNearby(QGraphicsSceneDragDropEvent *event);
    void adjustSceneRect();

//    ParameterizedItem *dropCompleteSample(const QString &name);

    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    QItemSelectionModel *m_selectionModel;
    bool m_block_selection;

    QMap<ParameterizedItem *, IView *> m_ItemToView;
    //!< COrrespondance of model's item and scene's view

    QLineF m_layer_interface_line;
    //!< foreground line representing appropriate interface during lauer's movement

    SampleViewAligner *m_aligner;

    NodeEditor *m_nodeEditor;
};


#endif


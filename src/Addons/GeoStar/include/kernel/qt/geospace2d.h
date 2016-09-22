#pragma once
#include <QtCore/qglobal.h>
#include <QWidget>
#include <QPainter>
#include <map.h>
#include <QMouseEvent>
#include <QWindow>
#include "../../utility/preconfig.h"
#include <QtGui>
KERNEL_NS
namespace QT{

class GS_API GsMapMouseEvent:public QMouseEvent
{
    double m_dblMapX,m_dblMapY;
public:
    GsMapMouseEvent(Type type, const QPointF &localPos, Qt::MouseButton button,
                Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers,double mapx,double mapy);
    double MapX()const;
    double MapY()const;
};

class GS_API GsGeoSpace2D:public QWindow
{
    Q_OBJECT
    QBackingStore m_backingStore;
    GsMapPtr m_ptrMap;
    bool m_bInner;
    GsSymbolTrackerPtr m_ptrTracker;

    GsSymbolTracker::GsTrackerFeedBack OnQueryByEnvelope(GsGeometry* geo);
    GsSymbolTracker::GsTrackerFeedBack OnSelectByEnvelope(GsGeometry* geo);
    GsSymbolTracker::GsTrackerFeedBack OnZoomIn(GsGeometry* geo);
    GsSymbolTracker::GsTrackerFeedBack OnZoomOut(GsGeometry* geo);
    QWidget* m_Widget;
public:
    GsGeoSpace2D(QWindow* parent = 0);
    ~GsGeoSpace2D();
    QWidget* Widget();
    void Widget(QWidget* w);


    GsMap* Map();
    void Update();
    void QueryByEnvelope();
    void SelectByEnvelope();
    void ZoomInEnv();
    void ZoomOutEnv();
    void ZoomPan();
    void AddLayer(GsLayer* pLyr);
    void RemoveLayer(GsLayer* pLyr);
    void ClearLayers();
    void ViewExtent(const GsBox& box);
    void DirtyMap();
protected:
    virtual bool event(QEvent *event) Q_DECL_OVERRIDE;

    virtual void resizeEvent(QResizeEvent *resizeEvent) Q_DECL_OVERRIDE;
    virtual void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;

    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void wheelEvent(QWheelEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);
    virtual void touchEvent(QTouchEvent *);
signals:
   void MouseDown(const GsMapMouseEvent& event);
   void MouseMove(const GsMapMouseEvent& event);
   void MouseUp(const GsMapMouseEvent& event);
   void QueryByGeometry(GsGeometry* geo);
   void LayerChanged();

};
}

KERNEL_ENDNS

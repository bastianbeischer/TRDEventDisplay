#include "GraphicsView.hh"

#include "Scene.hh"

// constructor
GraphicsView::GraphicsView(QWidget* parent) :
  QGraphicsView(parent),
  m_scene(new Scene()),
  m_zoomLevel(1.0)
{
  setGeometry(QRect(0,0,parent->width(),parent->height()));
  setScene(m_scene);
  
  QSizePolicy sizePol(QSizePolicy::Expanding,QSizePolicy::Expanding);
  setSizePolicy(sizePol);

  changeZoomLevel(5.0);

  //  fitInView(m_scene->sceneRect());
  show();
}

// destructor
GraphicsView::~GraphicsView()
{
  delete m_scene;
}


//! set new zoom level
void GraphicsView::changeZoomLevel(double newZoomLevel) 
{

  if (newZoomLevel != m_zoomLevel) {
    if (newZoomLevel < 1.0) newZoomLevel = 1.0;
    scale(newZoomLevel/m_zoomLevel, newZoomLevel/m_zoomLevel);
    setZoomLevel(newZoomLevel);
    emit zoomLevelChanged(newZoomLevel);
  }

}

//! zoom in
void GraphicsView::zoomIn() {

  double newZoom = 1.2*m_zoomLevel;;
  changeZoomLevel(newZoom);

}

//! zoom out
void GraphicsView::zoomOut() {

  double newZoom = m_zoomLevel/1.2;
  changeZoomLevel(newZoom);

}


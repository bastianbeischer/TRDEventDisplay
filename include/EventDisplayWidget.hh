/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: EventDisplayWidget.hh,v 1.3 2010/08/19 20:55:54 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef EventDisplayWidget_hh
#define EventDisplayWidget_hh

#include "DataWidget.hh"
#include "ui_EventDisplayForm.h"

class DataManager;
class EventDisplayScene;
class QResizeEvent;
class ZoomableView;

class EventDisplayWidget :
  public DataWidget,
  private Ui::EventDisplayForm
{
  
Q_OBJECT

public:
  EventDisplayWidget(const DataManager* dataManager, QWidget* parent = 0);
  ~EventDisplayWidget();
  
signals:
  int eventNumberChanged(int newNumber);

public slots:
  void fileOpened(int nEvents);
  void fileClosed();

private slots:
  void showEvent(int eventNumber);
  void updateScale();

protected:
  void resizeEvent(QResizeEvent* event);

private:
  ZoomableView*       m_view;
  EventDisplayScene*  m_scene;
  
};

#endif /* EventDisplayWidget_hh */

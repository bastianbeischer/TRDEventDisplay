/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: DataWidget.hh,v 1.1 2010/08/19 18:10:58 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef DataWidget_hh
#define DataWidget_hh

#include <QWidget>

class DataManager;

class DataWidget :
  public QWidget
{
  
public:
  DataWidget(const DataManager* dataManager, QWidget* parent = 0);
  ~DataWidget();
  
public slots:
  virtual void fileOpened(int nEvents) = 0;
  virtual void fileClosed() = 0;

protected:
  const DataManager*  m_dataManager;

};

#endif /* DataWidget_hh */

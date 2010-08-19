/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: DataWidget.cc,v 1.1 2010/08/19 18:10:59 beischer Exp $
/////////////////////////////////////////////////////////////////

#include "DataWidget.hh"

// constructor
DataWidget::DataWidget(const DataManager* dataManager, QWidget* parent) :
  QWidget(parent),
  m_dataManager(dataManager)
{
}

// destructor
DataWidget::~DataWidget()
{
}

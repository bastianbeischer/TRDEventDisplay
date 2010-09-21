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

#include "EventDisplayWidget.hh"

#include <QPalette>

#include "ColorScale.hh"
#include "DataManager.hh"
#include "EventDisplayScene.hh"
#include "ZoomableView.hh"

EventDisplayWidget::EventDisplayWidget(const DataManager* dataManager, QWidget* parent) :
  DataWidget(dataManager, parent),
  m_view(0),
  m_scene(new EventDisplayScene())
{
  // setup designer settings
  setupUi(this);

  // create graphics view and scene
  m_view = new ZoomableView(m_graphicsViewFrame);
  m_view->setScene(m_scene);
  int index = m_centralLayout->indexOf(m_graphicsViewFrame);
  int row, col, hozSpan, vertSpan;
  m_centralLayout->getItemPosition(index,&row,&col,&hozSpan,&vertSpan);
  m_centralLayout->addWidget(m_view,row,col,hozSpan,vertSpan);

  // add color palette
  QPalette palette;
  palette.setBrush(QPalette::Inactive, QPalette::Window, QBrush(*m_scene->scale()));
  palette.setBrush(QPalette::Active, QPalette::Window, QBrush(*m_scene->scale()));
  m_colorPaletteWidget->setPalette(palette);
  m_colorPaletteWidget->setAutoFillBackground(true);

  // connect signals and slots
  
  // event number
  connect(m_eventNumberSpinBox, SIGNAL(valueChanged(int)), this, SLOT(showEvent(int)));
  connect(this, SIGNAL(eventNumberChanged(int)), m_eventNumberSpinBox, SLOT(setValue(int)));

  // amplitude
  connect(m_minAmpSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateScale()));
  connect(m_maxAmpSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateScale()));
  connect(m_minAmpSpinBox, SIGNAL(valueChanged(int)), m_scene, SLOT(changeMinAmp(int)));
  connect(m_maxAmpSpinBox, SIGNAL(valueChanged(int)), m_scene, SLOT(changeMaxAmp(int)));

  // checkboxes for options
  connect(m_negAmpCheckBox, SIGNAL(stateChanged(int)), m_scene, SLOT(changeDisplayNegAmps(int)));
  connect(m_tubesWithNoHitsCheckBox, SIGNAL(stateChanged(int)), m_scene, SLOT(changeTubeWithNoHitsVisible(int)));

  // we can only fit the scene after the call to show
  show();
  m_view->fitScene();
}

EventDisplayWidget::~EventDisplayWidget()
{
  delete m_view;
  delete m_scene;
}

// a new file has been opened
void EventDisplayWidget::fileOpened(int nEvents)
{
  m_minAmpSpinBox->setEnabled(true);
  m_maxAmpSpinBox->setEnabled(true);
  m_negAmpCheckBox->setEnabled(true);
  m_tubesWithNoHitsCheckBox->setEnabled(true);

  m_eventNumberSpinBox->setMinimum(1);
  m_eventNumberSpinBox->setMaximum(nEvents);
  m_eventNumberSpinBox->setEnabled(true);

  QString text;
  text.sprintf("/ %d", nEvents);
  m_totalEventsLabel->setText(text);
  showEvent(1);
}

// the file has been closed
void EventDisplayWidget::fileClosed()
{
  m_minAmpSpinBox->setEnabled(false);
  m_maxAmpSpinBox->setEnabled(false);
  m_negAmpCheckBox->setEnabled(false);
  m_eventNumberSpinBox->setEnabled(false);  
  m_totalEventsLabel->setText("");
}

// show event
void EventDisplayWidget::showEvent(int eventNumber)
{
  const TrdRawEvent* event = m_dataManager->getEvent(eventNumber);
  if (event) {
    m_scene->processEvent(event);
    m_view->fitScene();
    emit(eventNumberChanged(eventNumber));
  }
}

// update labels under scale
void EventDisplayWidget::updateScale()
{
  double max = m_maxAmpSpinBox->value();
  double min = m_minAmpSpinBox->value();

  m_maxAmpSpinBox->setMinimum(min+1);
  m_minAmpSpinBox->setMaximum(max-1);

  double value;
  QString text;

  value = min;
  text.sprintf("%.0f", value);
  m_scaleLabelMin->setText(text);

  value = min + 0.25*(max-min);
  text.sprintf("%.0f", value);
  m_scaleLabel1->setText(text);

  value = min + 0.5*(max-min);
  text.sprintf("%.0f", value);
  m_scaleLabel2->setText(text);

  value = min + 0.75*(max-min);
  text.sprintf("%.0f", value);
  m_scaleLabel3->setText(text);

  value = max;
  text.sprintf("%.0f", value);
  m_scaleLabelMax->setText(text);
}

// resize the view when resizing the widget
void EventDisplayWidget::resizeEvent(QResizeEvent* event)
{
  QWidget::resizeEvent(event);
  m_view->fitScene();
}

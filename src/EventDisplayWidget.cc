#include "EventDisplayWidget.hh"

#include <QPalette>

#include "TrdRawEvent.hh"
#include "ColorScale.hh"
#include "DataManager.hh"
#include "EventDisplayScene.hh"
#include "ZoomableView.hh"

// constructor
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
  connect(this, SIGNAL(eventNumberChanged(int)), this, SLOT(adjustStatusLabels()));

  // amplitude
  connect(m_minAmpSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateScale()));
  connect(m_maxAmpSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateScale()));
  connect(m_minAmpSpinBox, SIGNAL(valueChanged(int)), m_scene, SLOT(changeScaleMin(int)));
  connect(m_maxAmpSpinBox, SIGNAL(valueChanged(int)), m_scene, SLOT(changeScaleMax(int)));

  // checkboxes for options
  connect(m_negAmpCheckBox, SIGNAL(stateChanged(int)), m_scene, SLOT(changeDisplayNegAmps(int)));
  connect(m_tubesWithNoHitsCheckBox, SIGNAL(stateChanged(int)), m_scene, SLOT(changeTubeWithNoHitsVisible(int)));

  // we can only fit the scene after the call to show
  show();
  m_view->fitScene();
}

// destructor
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

  m_runIdLabel->setText("");
  m_eventIdLabel->setText("");
  m_timeLabel->setText("");

  m_scene->removePreviousSignals();
  m_view->fitScene();
}

// show event
void EventDisplayWidget::showEvent(int eventNumber)
{
  const std::vector<TrdRawHitR>* hits = m_dataManager->getTrdHits(eventNumber);
  if (hits) {
    m_scene->processHits(*hits);
    m_view->fitScene();
    emit(eventNumberChanged(eventNumber));
  }
}

// update labels under scale
void EventDisplayWidget::updateScale()
{
  int max = m_maxAmpSpinBox->value();
  int min = m_minAmpSpinBox->value();

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

// print some information in the status bar
void EventDisplayWidget::adjustStatusLabels()
{
  QString runId = m_dataManager->getRunId();
  if (runId != "")
    runId = QString("Run ID: %1").arg(runId);

  QString eventId = m_dataManager->getEventId();
  if (eventId != "") {
    eventId = QString("Event ID: %1").arg(eventId);
  }

  QString time = m_dataManager->getTime();
  if (time != "") {
    time = QString("Time: %1").arg(time);
  }

  m_runIdLabel->setText(runId);
  m_eventIdLabel->setText(eventId);
  m_timeLabel->setText(time);
}

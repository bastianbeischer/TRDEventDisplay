#include "TrdScene.hh"

#include <QGraphicsRectItem>

#include "ColorScale.hh"
#include "StrawTube.hh"
#include "TrdHitRZD.hh"
#include "TrdRawHitR.hh"

// constructor
TrdScene::TrdScene() :
  QGraphicsScene(),
  m_scale(new ColorScale(0., 100.)),
  m_boundingBox(new QGraphicsRectItem()),
  m_width(200),
  m_height(70),
  m_z_offset(115.0)
{
  QRectF rectangle(-m_width/2., -m_height/2., m_width, m_height);
  setSceneRect(rectangle);
  m_boundingBox->setRect(rectangle);
  addItem(m_boundingBox);

  addTubesToScene();

  connect(this, SIGNAL(scaleMinChanged(int)), m_scale, SLOT(changeMin(int)));
  connect(this, SIGNAL(scaleMaxChanged(int)), m_scale, SLOT(changeMax(int)));
}

// destructor
TrdScene::~TrdScene()
{
  delete m_scale;
}

// add the rectangular representations of the tubes to the scene
void TrdScene::addTubesToScene()
{
  for(int lay=0;lay!=20;lay++){
    for(int lad=0;lad!=18;lad++){
      for(int tub=0;tub!=16;tub++){
        if(lay<4&&lad>13)continue;
        else if(lay<12&&lad>15)continue;
        else if(lay>19)continue;

        TrdRawHitR hit;
        hit.Layer = lay;
        hit.Ladder = lad;
        hit.Tube = tub;
        TrdHitRZD rzd(&hit);
        
        double x = rzd.r();
        double y = z_to_y(rzd.z());
        
        StrawTube* tube = new StrawTube(x,y);
        m_tubes.push_back(tube);
        addItem(tube);
      }
    }
  }
}

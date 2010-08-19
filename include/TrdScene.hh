/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: TrdScene.hh,v 1.3 2010/08/19 18:17:42 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef TrdScene_hh
#define TrdScene_hh

#include <QGraphicsScene>

#include <QList>

class ColorScale;
class StrawTube;

class TrdScene :
  public QGraphicsScene
{
  
Q_OBJECT

public:
  TrdScene();
  ~TrdScene();

signals:
  int scaleMinChanged(int min);
  int scaleMaxChanged(int max);

public slots:
  virtual void changeScaleMin(int min) {emit(scaleMinChanged(min));}
  virtual void changeScaleMax(int max) {emit(scaleMaxChanged(max));}

public:
  const ColorScale* scale() const {return m_scale;}

private:
  void addTubesToScene();

protected:
  double z_to_y(double z) {return -(z - m_z_offset);}

protected:
  ColorScale*                      m_scale;

  QList<StrawTube*>                m_tubes;
  
private:
  QGraphicsRectItem*               m_boundingBox;

  double                           m_width;
  double                           m_height;
  double                           m_z_offset;
  
};

#endif /* TrdScene_hh */

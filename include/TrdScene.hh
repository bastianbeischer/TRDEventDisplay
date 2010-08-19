/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: TrdScene.hh,v 1.1 2010/08/19 17:05:08 beischer Exp $
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
  int minChanged(int min);
  int maxChanged(int max);

public slots:
  virtual void changeMinAmp(int min) {emit(minChanged(min));}
  virtual void changeMaxAmp(int max) {emit(maxChanged(max));}

public:
  const ColorScale* scale() const {return m_scale;}

private:
  void addTubesToScene();

protected:
  double z_to_y(double z) {return -(z - m_z_offset);}

protected:
  ColorScale*                      m_scale;

  QGraphicsRectItem*               m_boundingBox;
  QList<StrawTube*>                m_tubes;
  
  double                           m_width;
  double                           m_height;
  double                           m_z_offset;
  
};

#endif /* TrdScene_hh */

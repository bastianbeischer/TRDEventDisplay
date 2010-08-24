/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: DataWidget.hh,v 1.3 2010/08/24 14:43:10 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef DataWidget_hh
#define DataWidget_hh

#include <QWidget>

class DataManager;

/**
 * @class DataWidget
 * 
 * @brief Abstract base class for all data displaying widgets
 *
 * This class is meant to provide a common interface to all data display widgets (i.e. EventDisplay, ...)
 * It is a purely virtual class and forces its children to implement fileOpened(int n) and fileClosed.
 */
class DataWidget :
  public QWidget
{
  
public:

  /**
   * @brief Constructor, sets up the m_dataManager pointer.
   */
  DataWidget(const DataManager* dataManager, QWidget* parent = 0);

  /**
   * @brief Destructor (does nothing).
   */
  ~DataWidget();
  
public slots:

  /**
   * @brief Purely virtual slot. Derived classes should implement something to do when a new file is available.
   */
  virtual void fileOpened(int nEvents) = 0;

  /**
   * @brief Purely virtual slot. Derived classes should implement something to do when the file is closed.
   */
  virtual void fileClosed() = 0;

protected:

  const DataManager*  m_dataManager; /**< Constant pointer to the data manager (initialized and "owned" by some other class) */

};

#endif /* DataWidget_hh */

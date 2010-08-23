/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: DataManager.hh,v 1.7 2010/08/23 13:57:49 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef DataManager_hh
#define DataManager_hh

#include <QObject>

class TFile;
class TTree;
class TrdRawEvent;
class TrdRawRun;

/**
 * @class DataManager
 * 
 * @brief Handles the interaction with the ROOT data files.
 *
 * This class maintains pointers to the current root file, tree and run. It opens and closes files as requested and emits
 * signals when a new file is available or the file has been closed. Data widgets can be connected to these signals in order
 * to take appropriate action.
 */
class DataManager :
  public QObject
{
  
Q_OBJECT

public:

  /**
   * @brief Constructor. Initializes everything to 0, except for the m_amsRootFileDir variable, which is set to the path of 
   *        $AMS_ROOTFILES_DIR if this environment variable is set.
   */
  DataManager();

  /**
   * @brief Destructor. Deletes all allocated members
   */
  ~DataManager();
  
signals:

  /**
   * @brief Signal for a new available file. Also transmits the number of events in the file.
   * @param nEvents The number of events in the new file. Note that this variable contains "output".
   */
  void fileOpened(int nEvents);

  /**
   * @brief Signal emitted when a file is closed.
   */
  void fileClosed();

public slots:

  /**
   * @brief Open a new file dialog, so that the user can choose a file top open.
   */
  void openFileDialog();

  /**
   * @brief Close the current file.
   */
  void closeFile();

public:

  /**
   * @brief Open file by fileName
   * @param fileName the path of the file to be opened
   */
  void openFile(QString fileName);

  /**
   * @brief Open file by naming scheme $AMS_ROOTFILES_DIR/XXXX/YYY.root. Requires $AMS_ROOTFILES_DIR to be set.
   * @param dir the directory part of the path (in the example above: XXXX)
   * @param file the filename part of the path (in the example above: YYY)
   */
  void openFileByScheme(int dir, int file);

  /**
   * @brief Return the event with number eventNumber
   * @param eventNumber the number of the event to be returned
   */
  const TrdRawEvent* getEvent(int eventNumber) const;

private:

  QString       m_amsRootFileDir; /**< QString which stores the content of $AMS_ROOTFILES_DIR, if set */

  TFile*        m_file;           /**< Pointer to the current file if available, otherwise = 0*/
  TTree*        m_tree;           /**< Pointer to the current tree if available, otherwise = 0. */
  TrdRawRun*    m_currentRun;     /**< Pointer to the current run if available, otherwise = 0. */

};

#endif /* DataManager_hh */

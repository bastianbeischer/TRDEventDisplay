#ifndef DataManager_hh
#define DataManager_hh

#include <QObject>
#include <vector>
#include "TrdRawHit.h"

class QDir;
class QTimer;
class TFile;
class TTree;
class TrdRawEvent;
class TrdRawRun;
class AMSChain;

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

  /**
   * @brief Signal emitted when the directory part of the path has changed
   */
  void dirNumberChanged(int dir);

  /**
   * @brief Signal emitted when the filename part of the path has changed
   */
  void fileNumberChanged(int file);

  /**
   * @brief Signal emitted when follow mode is started
   */
  void startedFollowing(bool really = true);
                         
  /**
   * @brief Signal emitted when follow mode is stopped
   */
  void stoppedFollowing(bool really = true);

public slots:

  /**
   * @brief Open a new Qt file dialog, so that the user can choose a file to open.
   */
  void openFileDialog();

  /**
   * @brief Open a new Qt file dialog, so that the user can choose an ams root file to open.
   */
  void openAmsRootFileDialog();

  /**
   * @brief Starts or stops following the latest ROOT files as they come.
   * @param start Whether to start or stop following.
   */
  void followFiles(bool start);

  /**
   * @brief Read the latest file
   */
  void readLatestFile();

  /**
   * @brief Close the current file.
   */
  void closeFile();

public:

  /**
   * @brief Open file by fileName
   * @param fileName the path of the file to be opened
   */
  int openFile(QString fileName);

  /**
   * @brief Open an AMS ROOT file by fileName
   * @param fileName the path of the file to be opened
   */
  int openAmsRootFile(QString fileName);

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
  const std::vector<TrdRawHitR>* getTrdHits(int eventNumber) const;

  /**
   * @brief The number of the current run
   * @return number of the current run as a string
   */
  const QString getRunId() const;

private:

  QDir*         m_dir;            /**< Directory with path $AMS_ROOTFILES_DIR, if this environment variable is set. */

  QTimer*       m_timer;          /**< Timer which triggers an attempt to read a new root file */

  TFile*        m_file;           /**< Pointer to the current file if available, otherwise = 0*/
  TTree*        m_tree;           /**< Pointer to the current tree if available, otherwise = 0. */
  TrdRawRun*    m_currentRun;     /**< Pointer to the current run if available, otherwise = 0. */

  AMSChain*     m_amsChain;       /**< Pointer to the ams chain */

};

#endif /* DataManager_hh */

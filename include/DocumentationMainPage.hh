/////////////////////////////////////////////////////////////////////
// CVS Information
// $Id: DocumentationMainPage.hh,v 1.5 2010/08/30 15:17:47 beischer Exp $
/////////////////////////////////////////////////////////////////

#ifndef DOCUMENATIONMAINPAGE_HH
#define DOCUMENATIONMAINPAGE_HH

/**
 *
 * @mainpage AMS Event Display Software
 *
 * @author Bastian Beischer <beischer AT physik.rwth-aachen.de>
 * @date Mon Aug 23 13:45:00 2010
 *
 * @brief This program was designed to show single events recorded in the AMS testbeam of August 2010.
 *        It reads ROOT files from the testbeam data set and displays the events contained therein.
 *
 * \section build Building the program
 *
 * This program is based on Qt 4 (http://qt.nokia.com), a (among other things) gui toolkit which is freely available in open source form.  The Qt
 * version used while writing the software was Qt 4.6.3. A version >= 4.5 is recommended for problem-free operation. A recent version of Qt is
 * available for most Linux distributions from their respective repositories. Qt is also available for MS Windows allowing this program to run there,
 * but the build files shipped with this project (.pro and .pri files) probably will not allow a successful build there, yet. Feel free to modify
 * them and commit your changes if you plan to run this program in MS Windows.
 *
 * The program is mainted with git and has a public github repository. In order to pull the latest changes just execute:
 * \verbatim git pull \endverbatim
 *
 * If you want to commit changes you need to get yourself a github.com account and contact me (beischer@physik.rwth-aachen.de) so that I can add you
 * as a collaborator on github.
 *
 * A successful build of the program requires the following prerequisites:
 * - Qt >= 4.5 (version confirmed to work: 4.6.3)
 * - recent ROOT (version confirmed to work: 5.27.04)
 * - GCC (version confirmed to work: 4.5.1)
 * - (optional) doxygen: For generation of the documentation (version confirmed to work: doxygen 1.7.1)
 * - (optional) etags: for emacs TAGS generation (version confirmed to work: etags from emacs 23.2)
 *
 * In order to build the program issue the following commands from the main project directory:
 * \verbatim qmake; make\endverbatim
 * 
 * This builds the main executable "./EventDisplay", the prerequisite library libTrdEvent.so and the emacs TAGS file if "etags" is available.
 *
 * This documentation can be built with:
 * \verbatim make doc\endverbatim
 *
 * \section start Starting the program
 *
 * Before running the program you should make sure that the library libTrdEvent is in your LD_LIBRARY_PATH.
 *
 * The program can be started with
 * \verbatim ./EventDisplay\endverbatim
 * 
 * Open a ROOT file directly with:
 * \verbatim ./EventDisplay path/to/file.root\endverbatim
 *
 * If you have the AMS_ROOTFILES_DIR variable set you can also use the following scheme:
 * \verbatim ./EventDisplay XXXX YYY\endverbatim
 * where XXXX is the directory in which the file resides and YYY is its three-digit filename.
 * Example: 0001 001 could correspond to /tmp/rootrawdata/HRDL-B/0001/001.root with AMS_ROOTFILES_DIR=/tmp/rootrawdata/HRDL-B
 *
 * \section use Using the program
 *
 * First, open a valid ROOT file 
 *   There are various alternative methods:

 *   - Use the start parameters above to open a file when starting the program
 *   - Click the "Open File" button (or press Alt+o)
 *   - Click the "Follow Latest Files" button (or press Alt+f) to enter "follow" mode. In this mode, the program will constantly scan for new files
 *     every 60 seconds and open the latest one available in the AMS_ROOTFILES_DIR directory. The variable has to be set for this to work.
 *   - Use the provided spin boxes to navigate to a file. Press the "Synchronized" button to read the values from the spin boxes. In "synchronized"
 *     mode every change to the spin box values will be applied directly.
 *
 * You can then proceed in the following way:
 *
 * - Use the event number spin box to scroll through the available events.
 * - You can zoom in a specific region of interest with the mouse wheel or by drawing a rectangle with the right mouse button pressed. Un-zoom by
 *   clicking the middle mouse button.
 * - The scene can be scrolled by the scroll-bars at the sides or by left-clicking and dragging the scene.
 * - Use the min/max spin boxes to change the scale of the plot
 *
 */

#endif

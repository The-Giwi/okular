/***************************************************************************
 *   Copyright (C) 2002 by Wilco Greven <greven@kde.org>                   *
 *   Copyright (C) 2003 by Benjamin Meyer <benjamin@csh.rit.edu>           *
 *   Copyright (C) 2003 by Laurent Montel <montel@kde.org>                 *
 *   Copyright (C) 2003 by Luboš Luňák <l.lunak@kde.org>                   *
 *   Copyright (C) 2004 by Christophe Devriese                             *
 *                         <Christophe.Devriese@student.kuleuven.ac.be>    *
 *   Copyright (C) 2004 by Albert Astals Cid <tsdgeos@terra.es>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _KPDF_SHELL_H_
#define _KPDF_SHELL_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kparts/mainwindow.h>
#include <kmimetype.h>

namespace KPDF
{
class Part;
  /**
   * This is the application "Shell".  It has a menubar and a toolbar
   * but relies on the "Part" to do all the real work.
   *
   * @short Application Shell
   * @author Wilco Greven <greven@kde.org>
   * @version 0.1
   */
  class Shell : public KParts::MainWindow
  {
    Q_OBJECT

  public:
    /**
     * Default Constructor
     */
    Shell();

    /**
     * Open an url
     */
    Shell(const KURL &url);

    /**
     * Default Destructor
     */
    virtual ~Shell();

  protected:
    /**
     * This method is called when it is time for the app to save its
     * properties for session management purposes.
     */
    void saveProperties(KConfig*);

    /**
     * This method is called when this app is restored.  The KConfig
     * object points to the session management config file that was saved
     * with @ref saveProperties
     */
    void readProperties(KConfig*);
    void readSettings();
    void writeSettings();
    void setFullScreen( bool );
    
  private slots:
    void fileOpen();
    void slotQuit();

    void optionsConfigureToolbars();
    void applyNewToolbarConfig();
    void slotUpdateFullScreen();
    void slotShowMenubar();

    void openURL( const KURL & url );
    void delayedOpen();

  signals:
    void restoreDocument(const KURL &url, int page);
    void saveDocumentRestoreInfo(KConfig* config);

  private:
    void setupAccel();
    void setupActions();
    void init();
    bool handleCompressed(KURL & url, const QString &path, const KMimeType::Ptr mimetype);
    QStringList* fileFormats();

  private:
    KParts::ReadOnlyPart* m_part;
    KRecentFilesAction* m_recent;
    QStringList* m_fileformats;
    KAction* m_printAction;
    KToggleAction* m_fullScreenAction;
    KToggleAction* m_showMenuBarAction;
    KToggleAction* m_showToolBarAction;
    bool m_menuBarWasShown, m_toolBarWasShown;
    KURL m_openUrl;
  };
}

#endif

// vim:ts=2:sw=2:tw=78:et

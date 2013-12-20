#include "Dialogs/databaseconnectiondialog.h"
#include "Dialogs/Preference/preferencedialog.h"
#include "connectionwidget.h"
#include "mainwindow.h"
#include "mdichild.h"
#include <QtWidgets> // иначе не работет qApp

MainWindow::MainWindow()

{
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(updateMenus()));

    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget*)),
                this, SLOT(setActiveSubWindow(QWidget*)));

    readSettings();
    setLanguage();
    createActions();
    createMenu();
    updateMenus();
    createDockWidget();
    retranslate(language);
    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{
    writeSettings();
}

MdiChild *MainWindow::activeMdiChild()
{
    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return 0;
}

void MainWindow::closeWindow()
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Attention !!!"),tr("Close current connection ?"),
                               QMessageBox::Ok | QMessageBox::Cancel);
    if (ret == QMessageBox::Ok){
        mdiArea->closeActiveSubWindow();
        return;
    }
    if (ret == QMessageBox::Cancel){
        return;
    }
}

void MainWindow::createActions()
{
    closeAct = new QAction(this);
    closeAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
    closeAct->setStatusTip(tr("close current window and connection"));
    connect(closeAct, SIGNAL(triggered()),
            this, SLOT(closeWindow()));

    closeAllAct = new QAction(this);
    closeAllAct->setStatusTip(tr("close all windows and connections"));

    dbConnectionAct = new QAction(this);
    dbConnectionAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    dbConnectionAct->setIcon(QIcon(":/images/disconnect32.png"));
    dbConnectionAct->setStatusTip(tr("database connection"));
    connect(dbConnectionAct, SIGNAL(triggered()), this, SLOT(dbConnection()));

    aboutQtAct = new QAction(this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    exitAct = new QAction(this);
    exitAct->setIcon(QIcon(":/images/exit32.png"));
    exitAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    preferenceAct = new QAction(this);
    connect(preferenceAct, SIGNAL(triggered()), this, SLOT(preference()));

    actionGroup = new QActionGroup(this);
    separatorAct = new QAction(this);
    separatorAct->setSeparator(true);
}

void MainWindow::createDockWidget()
{
    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    viewMenu->addAction(dock->toggleViewAction());
    connWidget = new ConnectionWidget(this);
    dock->setWidget(connWidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}

MdiChild *MainWindow::createMdiChild()
{
    MdiChild *child = new MdiChild;
//    child->setModel();
    mdiArea->addSubWindow(child);

#ifndef QT_NO_CLIPBOARD
//    connect(child, SIGNAL(copyAvailable(bool)),
//            cutAct, SLOT(setEnabled(bool)));
//    connect(child, SIGNAL(copyAvailable(bool)),
//            copyAct, SLOT(setEnabled(bool)));
#endif

    return child;
}

void MainWindow::createMenu()
{
    mainMenu    = new QMenu(this);
    mainMenu    ->addAction(dbConnectionAct);
    mainMenu    ->addAction(exitAct);

    editMenu    = new QMenu(this);
    viewMenu    = new QMenu(this);
    windowMenu  = new QMenu(this);
    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    serviceMenu = new QMenu(this);
    serviceMenu ->addAction(preferenceAct);

    helpMenu    = new QMenu(this);
    helpMenu    ->addAction(aboutQtAct);

    menuBar()->addMenu(mainMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(windowMenu);
    menuBar()->addMenu(serviceMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::dbConnection()
{
    DatabaseConnectionDialog *dialog = new DatabaseConnectionDialog(this);
    dialog->setDatabaseDriverName(driverName);
    dialog->setDatabaseHostName(hostName);
    dialog->setDatabasePortNumber(portNumber);
    dialog->setDatabaseName(dbName);
    dialog->setDatabaseUsername(userName);
    dialog->exec();

    driverName  = dialog->driverName();
    hostName    = dialog->hostName();
    portNumber  = dialog->portNumber();
    dbName      = dialog->dbName();
    userName    = dialog->userName();

    setIcon();
    QString nameDB = dialog->connectName();
    if(QSqlDatabase::database(nameDB).isOpen()){
        openMdiChild(nameDB);
        connWidget->refresh();
        connect(connWidget, SIGNAL(tableActivated(QString)), this, SLOT(showTable(QString)));
    }
    updateWindowMenu();
//        QMessageBox::warning(this,tr("dbConnection"), nameDB);

}

QDir MainWindow::directoryOf(const QString &subdir)
{
    QDir dir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (dir.dirName.toLower() == "debug"
            || dirName().toLower() == "release")
        dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(subdir);
    return dir;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &windowObjectName)
{
    foreach (QMdiSubWindow *window, mdiArea->subWindowList()) {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if (mdiChild->objectName() == windowObjectName)
            return window;
    }
    return 0;
}

void MainWindow::openMdiChild(const QString &connectionName)
{
    QMdiSubWindow *existing = findMdiChild(connectionName);
    if (existing) {
        mdiArea->setActiveSubWindow(existing);
        return;
    }

    MdiChild *child = createMdiChild();
    child->setObjectName(connectionName);
    child->setWindowTitle(connectionName);
    child->show();
}

void MainWindow::preference()
{
    PreferenceDialog dialog; //диалог насройка приложения слот
    dialog.setLanguageCombo(language);
    dialog.exec();

    if(dialog.locale != "")language = dialog.locale;
    retranslate(language);

}

void MainWindow::readSettings()
{
    QSettings settings("QtProject", "MC1");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("/size",sizeHint()).toSize();
    if(size.isNull()) resize(650,450);
    move(pos);
    resize(size);
    language = settings.value("/Settings/language","").toString();
    driverName = settings.value("/Settings/driverName", "").toString();
    hostName    = settings.value("/Settings/hostName","").toString();
    portNumber  = settings.value("/Settings/portNumber",3306).toInt();
    dbName      = settings.value("/Settings/dbName","").toString();
    userName    = settings.value("/Settings/userName","").toString();
}

void MainWindow::retranslate(QString lang)
{
    aboutQtAct      ->setText(tr("About &Qt"));
    closeAct        ->setText(tr("Close"));
    closeAllAct     ->setText(tr("CloseAll"));
    dbConnectionAct ->setText(tr("Connection"));
    exitAct         ->setText(tr("Exit"));
    preferenceAct   ->setText(tr("Preference..."));

    mainMenu    ->setTitle(tr("Main"));
    editMenu    ->setTitle(tr("Edit"));
    viewMenu    ->setTitle(tr("View"));
    windowMenu  ->setTitle(tr("Window"));
    serviceMenu ->setTitle(tr("Service"));
    helpMenu    ->setTitle(tr("Help"));

    QString qmPath = directoryOf("translations").absolutePath();
    qtTranslator.load("qt_"+lang, qmPath);
    qApp->installTranslator(&qtTranslator);
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::setIcon()
{
    QStringList names = QSqlDatabase::connectionNames();
    if(!names.isEmpty()) dbConnectionAct->setIcon(QIcon(":/images/connectDB32_32.png"));
    else dbConnectionAct->setIcon(QIcon(":/images/disconnect32.png"));
}

void MainWindow::setLanguage()
{//спользуем эту функцию для начального задания языка приложения
    if (language == tr("")) {
        language = QLocale::system().name();
        language.chop(3);
    }
}

void MainWindow::showTable(const QString &t)
{
     QString name = connWidget->currentDatabase().connectionName();
     openMdiChild(name);

     QSqlTableModel *model = new CustomModel(activeMdiChild(), connWidget->currentDatabase());
     model->setEditStrategy(QSqlTableModel::OnRowChange);
     model->setTable(connWidget->currentDatabase().driver()->escapeIdentifier(t, QSqlDriver::TableName));
     model->select();
     if (model->lastError().type() != QSqlError::NoError)
         emit statusMessage(model->lastError().text());
     activeMdiChild()->setModel(model);
     activeMdiChild()->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
     activeMdiChild()->setWindowTitle(name + ": " + t);
}

void MainWindow::updateMenus()
{
    bool hasMdiChild = (activeMdiChild() != 0);
    closeAct->setEnabled(hasMdiChild);
    closeAllAct->setEnabled(hasMdiChild);
}

void MainWindow::updateWindowMenu()
{
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();

    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
    for (int i=0; i < windows.size(); ++i){
        MdiChild *child = qobject_cast<MdiChild *>(windows.at(i)->widget());
        QString text;
        text = tr("%1 %2").arg(i+1).arg(child->objectName());
        QAction *action = windowMenu->addAction(text/*child->objectName()*/);
        actionGroup->addAction(action);
        action->setCheckable(true);
        action->setChecked(child == activeMdiChild());
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows.at(i));
    }
}

void MainWindow::writeSettings()
{
    QSettings settings("QtProject", "MC1");
    settings.setValue("pos", pos());
    settings.setValue("/size",size());
    settings.setValue("/Settings/language", language);
    settings.setValue("/Settings/driverName", driverName);
    settings.setValue("/Settings/hostName", hostName);
    settings.setValue("/Settings/portNumber", portNumber);
    settings.setValue("/Settings/dbName", dbName);
    settings.setValue("/Settings/userName", userName);
}

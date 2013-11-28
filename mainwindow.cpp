#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    readSettings();

    createActions();
    createMenu();
    retranslate();
}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::createActions()
{
    aboutQtAct = new QAction(this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    exitAct = new QAction(this);
    exitAct->setIcon(QIcon(":/images/exit32.png"));
    exitAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
}

void MainWindow::createMenu()
{
    mainMenu    = new QMenu(this);
    mainMenu    ->addAction(exitAct);

    editMenu    = new QMenu(this);
    viewMenu    = new QMenu(this);
    windowMenu  = new QMenu(this);
    serviceMenu = new QMenu(this);

    helpMenu    = new QMenu(this);
    helpMenu    ->addAction(aboutQtAct);

    menuBar()->addMenu(mainMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(windowMenu);
    menuBar()->addMenu(serviceMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::readSettings()
{
    QSettings settings("QtProject", "MC1");
    QSize size = settings.value("/size",sizeHint()).toSize();
    if(size.isNull()) resize(650,450);
    resize(size);
}

void MainWindow::retranslate()
{
    aboutQtAct      ->setText(tr("About &Qt"));
    exitAct     ->setText(tr("Exit"));

    mainMenu    ->setTitle(tr("Main"));
    editMenu    ->setTitle(tr("Edit"));
    viewMenu    ->setTitle(tr("View"));
    windowMenu  ->setTitle(tr("Window"));
    serviceMenu ->setTitle(tr("Service"));
    helpMenu    ->setTitle(tr("Help"));
}

void MainWindow::writeSettings()
{
    QSettings settings("QtProject", "MC1");
    settings.setValue("/size",size());
}

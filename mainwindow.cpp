#include "Dialogs/databaseconnectiondialog.h"
#include "Dialogs/Preference/preferencedialog.h"
#include "mainwindow.h"
#include <QtWidgets> // иначе не работет qApp

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    readSettings();
    setLanguage();
    createActions();
    createMenu();
    retranslate(language);
}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::createActions()
{
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
}

void MainWindow::createMenu()
{
    mainMenu    = new QMenu(this);
    mainMenu    ->addAction(dbConnectionAct);
    mainMenu    ->addAction(exitAct);

    editMenu    = new QMenu(this);
    viewMenu    = new QMenu(this);
    windowMenu  = new QMenu(this);

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
    dialog->exec();
//    QMessageBox::warning(this, tr(""),"void dbConnection();");
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
    QSize size = settings.value("/size",sizeHint()).toSize();
    if(size.isNull()) resize(650,450);
    resize(size);
    language = settings.value("/Settings/language","").toString();
}

void MainWindow::retranslate(QString lang)
{
    aboutQtAct      ->setText(tr("About &Qt"));
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

void MainWindow::setLanguage()
{//спользуем эту функцию для начального задания языка приложения
    if (language == tr("")) {
        language = QLocale::system().name();
        language.chop(3);
    }
}

void MainWindow::writeSettings()
{
    QSettings settings("QtProject", "MC1");
    settings.setValue("/size",size());
    settings.setValue("/Settings/language", language);
}

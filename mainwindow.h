#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTranslator>

class QDir;
class ConnectionWidget;
class QMdiArea;
class MdiChild;
class QMdiSubWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void dbConnection();
    void preference();

private:
    void createActions();
    void createDockWidget();
    MdiChild *createMdiChild();
    void createMenu();
    QDir directoryOf(const QString &subdir);
    void openMdiChild(const QString &connectionName);
    void readSettings();
    void retranslate(QString lang);
    void setIcon();
    void setLanguage();
    void writeSettings();

    QMdiSubWindow *findMdiChild(const QString &windowObjectName);

    ConnectionWidget *connWidget;

    QAction     *aboutQtAct;
    QAction     *dbConnectionAct;
    QAction     *exitAct;
    QAction     *preferenceAct;

    QMdiArea    *mdiArea;
    QMenu *mainMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *windowMenu;
    QMenu *serviceMenu;
    QMenu *helpMenu;

    QTranslator qtTranslator;
    QString     dbName;
    QString     driverName;
    QString     hostName;
    int         portNumber;
    QString     userName;
    QString     language;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTranslator>

class QDir;
class ConnectionWidget;

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
    void createMenu();
    QDir directoryOf(const QString &subdir);
    void readSettings();
    void retranslate(QString lang);
    void setIcon();
    void setLanguage();
    void writeSettings();

    ConnectionWidget *connWidget;

    QAction     *aboutQtAct;
    QAction     *dbConnectionAct;
    QAction     *exitAct;
    QAction     *preferenceAct;

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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTranslator>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void preference();

private:
    void createActions();
    void createMenu();
    void readSettings();
    void retranslate(QString lang);
    void setLanguage();
    void writeSettings();

    QAction     *aboutQtAct;
    QAction     *exitAct;
    QAction     *preferenceAct;

    QMenu *mainMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *windowMenu;
    QMenu *serviceMenu;
    QMenu *helpMenu;

    QTranslator qtTranslator;
    QString language;
};

#endif // MAINWINDOW_H

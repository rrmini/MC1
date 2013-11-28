#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void createActions();
    void createMenu();
    void readSettings();
    void retranslate();
    void writeSettings();

    QAction     *aboutQtAct;
    QAction     *exitAct;

    QMenu *mainMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *windowMenu;
    QMenu *serviceMenu;
    QMenu *helpMenu;
};

#endif // MAINWINDOW_H

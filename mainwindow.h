#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTranslator>
#include <QtSql>

class QDir;
class ConnectionWidget;
class QMdiArea;
class MdiChild;
class QMdiSubWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(/*QWidget *parent = 0*/);
    ~MainWindow();

private slots:
    void closeWindow();
    void dbConnection();
    void preference();
    void setActiveSubWindow(QWidget *window);
    void showTable(const QString &table);
    void updateMenus();
    void updateWindowMenu();

private:
    MdiChild    *activeMdiChild();
    void        createActions();
    void        createDockWidget();
    MdiChild    *createMdiChild();
    void        createMenu();
    QDir        directoryOf(const QString &subdir);
    void        openMdiChild(const QString &connectionName);
    void        readSettings();
    void        retranslate(QString lang);
    void        setIcon();
    void        setLanguage();
    void        writeSettings();

    QMdiSubWindow *findMdiChild(const QString &windowObjectName);

    ConnectionWidget *connWidget;

    QAction     *aboutQtAct;
    QAction     *closeAct;
    QAction     *closeAllAct;
    QAction     *dbConnectionAct;
    QAction     *exitAct;
    QAction     *preferenceAct;
    QAction     *separatorAct;
    QActionGroup *actionGroup;

    QMdiArea    *mdiArea;
    QMenu *mainMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *windowMenu;
    QMenu *serviceMenu;
    QMenu *helpMenu;

    QTranslator qtTranslator;
    QSignalMapper *windowMapper;
    QString     dbName;
    QString     driverName;
    QString     hostName;
    int         portNumber;
    QString     userName;
    QString     language;

signals:
    void statusMessage(const QString &message);
};

class CustomModel: public QSqlTableModel
{
    Q_OBJECT
public:
    explicit CustomModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase()):QSqlTableModel(parent, db) {}
    QVariant data(const QModelIndex &idx, int role) const
    {
        if (role == Qt::BackgroundRole && isDirty(idx))
            return QBrush(QColor(Qt::yellow));
        return QSqlTableModel::data(idx, role);
    }
};
#endif // MAINWINDOW_H

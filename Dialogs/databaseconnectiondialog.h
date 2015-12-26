#ifndef DATABASECONNECTIONDIALOG_H
#define DATABASECONNECTIONDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtWidgets>

class DatabaseConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DatabaseConnectionDialog(QWidget *parent = 0);

    void setDatabaseName( const QString& dbName );
    void setDatabasePortNumber( int& portNumber );
    void setDatabaseHostName( const QString& hostname );
    void setDatabaseUsername( const QString& username );
    void setDatabaseDriverName( const QString& drvName );
    int portNumber();
    const QString connectName();
    const QString dbName();
    const QString driverName();
    const QString hostName();
    const QString userName();

signals:

private slots:
    void slotPerformConnection();
    bool slotCheckFormData();

private:
    QComboBox* comboDatabaseDriverName;

    QDialogButtonBox* buttons;

    QGroupBox* gridGroupBox;
    QGroupBox* urlGroupBox;

    QLabel* labelDatabaseDriverName;
    QLabel* labelDatabasePort;
    QLabel* labelDatabaseName;
    QLabel* labelDatabaseHostName;
    QLabel* labelDatabaseUsername;
    QLabel* labelDatabasePassword;
    QLabel* labelDatabaseURL;

    QLineEdit* editDatabaseHostName;
    QLineEdit* editDatabaseName;
    QLineEdit* editDatabasePassword;
    QLineEdit* editDatabaseUsername;

    QSpinBox* spinBoxDatabasePort;

    QString connectionName;

    bool checkFormData();
    void createGridGroupBox();
    void createUrlGroupBox();
    void createWidgets();
    void doDatabaseConnection();
    void findAvailableDrivers();
    void setConnectionName(const QString& str);
    void setUpGUI();
};

#endif // DATABASECONNECTIONDIALOG_H

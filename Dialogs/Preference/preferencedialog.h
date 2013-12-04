#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>

class ConfigurationPage;
class QListWidget;
class QListWidgetItem;
class QStackedWidget;

class PreferenceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreferenceDialog(/*QObject *parent = 0*/);

    void setLanguageCombo(QString str);
    QString locale;

signals:

public slots:
    void apply();
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void okToContinue();
    void windowModified();

private:
    void createIcons();

    ConfigurationPage *confPage;
    QListWidget *contentsWidget;
    QPushButton *applyButton;
    QStackedWidget *pagesWidget;
};

#endif // PREFERENCEDIALOG_H

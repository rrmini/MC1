#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include <QWidget>

class QTreeWidget;
class QTreeWidgetItem;

class ConnectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectionWidget(QWidget *parent = 0);

signals:
    void metaDataRequested(const QString &tableName);

public slots:
    void refresh();
    void showMetaData();

private:
    void setActive(QTreeWidgetItem *item);

    QAction *metaDataAction;
    QTreeWidget *tree;
    QString activeDb;
};

#endif // CONNECTIONWIDGET_H

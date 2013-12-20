#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include <QWidget>

class QSqlDatabase;
class QTreeWidget;
class QTreeWidgetItem;

class ConnectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectionWidget(QWidget *parent = 0);

    QSqlDatabase currentDatabase() const;

signals:
    void metaDataRequested(const QString &tableName);
    void tableActivated(const QString &table);

public slots:
    void refresh();
    void showMetaData();
    void on_tree_itemActivated(QTreeWidgetItem *item, int);

private:
    void setActive(QTreeWidgetItem *item);

    QAction *metaDataAction;
    QTreeWidget *tree;
    QString activeDb;
};

#endif // CONNECTIONWIDGET_H

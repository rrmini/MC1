#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include <QWidget>

class QTreeWidget;

class ConnectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectionWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QAction *metaDataAction;
    QTreeWidget *tree;
};

#endif // CONNECTIONWIDGET_H

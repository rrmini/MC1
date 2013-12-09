#include <QtWidgets>
#include "connectionwidget.h"

ConnectionWidget::ConnectionWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    tree = new QTreeWidget(this);
    tree->setObjectName(QLatin1String("tree"));
    tree->setHeaderLabels(QStringList(tr("database")));
    tree->header()->setSectionResizeMode(QHeaderView::Stretch);
    QAction *refreshAction = new QAction(tr("Refresh"), tree);
    metaDataAction = new QAction(tr("Show Schema"), tree);
//    connect(refreshAction, SIGNAL(triggered()), SLOT(refresh()));
//    connect(metaDataAction, SIGNAL(triggered()), SLOT(showMetaData()));
    tree->addAction(refreshAction);
    tree->addAction(metaDataAction);
    tree->setContextMenuPolicy(Qt::ActionsContextMenu);
//    connect(tree, SIGNAL(itemActivated(QTreeWidgetItem*,int)),
//            this, SLOT(on_tree_itemActivated(QTreeWidgetItem*,int)));
//    connect(tree, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
//            this, SLOT(on_tree_currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));

    layout->addWidget(tree);
    QLineEdit *lineEdit = new QLineEdit(this);
    layout->addWidget(lineEdit);
}

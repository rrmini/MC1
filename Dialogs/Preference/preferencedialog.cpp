#include <QtWidgets>

#include "preferencedialog.h"
#include "pages.h"

PreferenceDialog::PreferenceDialog()
{
    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);

    pagesWidget = new QStackedWidget;
    confPage = new ConfigurationPage;
    pagesWidget->addWidget(/*new ConfigurationPage*/confPage);
    connect(confPage->languageCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(windowModified()));

    QDialogButtonBox* buttons = new QDialogButtonBox( this );
    buttons->addButton( QDialogButtonBox::Ok);
    buttons->addButton( QDialogButtonBox::Cancel);
    buttons->addButton( QDialogButtonBox::Apply);

    applyButton = buttons->button(QDialogButtonBox::Apply);
    connect(applyButton, SIGNAL(clicked()),this, SLOT(apply()));

    createIcons();
    contentsWidget->setCurrentRow(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(buttons);
    connect(buttons, SIGNAL(rejected()), this, SLOT(close()));
    connect(buttons, SIGNAL(accepted()), this, SLOT(okToContinue()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Config Dialog[*]"));
    setWindowModified(false);
}

void PreferenceDialog::apply()
{
    int currentIndex = confPage->languageCombo->currentIndex();
    switch(currentIndex){
    case 0:locale = tr("en");
        break;
    case 1: locale = tr("ru");
        break;
    case 2: locale = tr("de");
        break;
    }
    applyButton->setEnabled(false);
    setWindowModified(false);
}

void PreferenceDialog::createIcons()
{
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setText(tr("Configuration"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void PreferenceDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

void PreferenceDialog::okToContinue()
{
    if(isWindowModified()){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Attention !!!"),tr("Save the changes ?"),
                                   QMessageBox::Save | QMessageBox::Cancel);
        if (ret == QMessageBox::Save){
            apply();
            close();
        }
        if (ret == QMessageBox::Cancel){
            return;
        }
    }
    close();
}

void PreferenceDialog::setLanguageCombo(QString str)
{
    if(str == "en") confPage->languageCombo->setCurrentIndex(0);
    if(str == "ru") confPage->languageCombo->setCurrentIndex(1);
    if(str == "de") confPage->languageCombo->setCurrentIndex(2);
    applyButton->setEnabled(false);
    setWindowModified(false);
}

void PreferenceDialog::windowModified()
{
    applyButton->setEnabled(true);
    setWindowModified(true);
}

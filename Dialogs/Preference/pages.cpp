#include <QtWidgets>
#include "pages.h"

ConfigurationPage::ConfigurationPage(QWidget *parent) :
    QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Location"));

    QLabel *serverLabel = new QLabel(tr("Language:"));
    languageCombo = new QComboBox;
    languageCombo->addItem(tr("English"));
    languageCombo->addItem(tr("Russian"));
    languageCombo->addItem(tr("German"));
//    languageCombo->addItem(tr("Qt (People's Republic of China)"));
//    languageCombo->addItem(tr("Qt (USA)"));

    QHBoxLayout *serverLayout = new QHBoxLayout;
    serverLayout->addWidget(serverLabel);
    serverLayout->addWidget(languageCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(serverLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}


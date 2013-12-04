#ifndef PAGES_H
#define PAGES_H

#include <QWidget>

class ConfigurationPage : public QWidget
{
public:
    explicit ConfigurationPage(QWidget *parent = 0);
    QComboBox *languageCombo;
};

#endif // PAGES_H

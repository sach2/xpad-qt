#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <memory>
#include <QColorDialog>
#include <properties.h>

namespace Ui {
class PreferencesWindow;
}

class PreferencesWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit PreferencesWindow(Properties prop, QWidget *parent = 0);
    ~PreferencesWindow();
    Properties GetProperties();
private:
    Ui::PreferencesWindow *ui;
    Properties properties, confirmedProperties;
    std::unique_ptr<QColorDialog> textColorSelector;
    std::unique_ptr<QColorDialog> backColorSelector;

    void onTextColorButtonPressed();
    void onBackColorButtonPressed();

    void DrawPreview();
};

#endif // PREFERENCES_H

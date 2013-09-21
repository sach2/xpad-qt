#ifndef PROPERTIESWINDOW_H
#define PROPERTIESWINDOW_H

#include <QDialog>
#include <properties.h>
#include <QColorDialog>
#include <memory>

namespace Ui {
class PropertiesWindow;
}

class PropertiesWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit PropertiesWindow(Properties prop, QWidget *parent = 0);
    ~PropertiesWindow();
    Properties GetProperties();
private:
    Ui::PropertiesWindow *ui;
    Properties properties, confirmedProperties;
    std::unique_ptr<QColorDialog> textColorSelector;
    std::unique_ptr<QColorDialog> backColorSelector;

    void onTextColorButtonPressed();
    void onBackColorButtonPressed();

    void DrawPreview();
};

#endif // PROPERTIESWINDOW_H

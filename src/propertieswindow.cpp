#include "propertieswindow.h"
#include "ui_propertieswindow.h"
#include <QDebug>
#include <functional>

PropertiesWindow::PropertiesWindow(Properties prop, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertiesWindow),
    properties(prop),
    confirmedProperties(prop)
{
    ui->setupUi(this);
    DrawPreview();
    connect(ui->textColorButton, &QPushButton::pressed,
            this, &PropertiesWindow::onTextColorButtonPressed);
    connect(ui->backColorButton, &QPushButton::pressed,
            this, &PropertiesWindow::onBackColorButtonPressed);
    // todo: find alternative, don't get accepted signal directly, so emitting manually
    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            [&]()
            {
                hide();
                emit accepted();
            }
    );
    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            [&]()
            {
                hide();
                emit rejected();
            }
    );
    ui->backColorButton->setShortcut(QKeySequence::New);
}

void PropertiesWindow::onTextColorButtonPressed()
{
    if (! textColorSelector)
    {
        textColorSelector.reset(new QColorDialog());
        textColorSelector->setWindowTitle("Select Text Color");
        connect(textColorSelector.get(), &QColorDialog::rejected,
                [&]()
                {
                    // revert, reset
                    properties.textColor = confirmedProperties.textColor;
                    DrawPreview();
                    textColorSelector.reset();
                }
        );
        connect(textColorSelector.get(),&QColorDialog::currentColorChanged,
                [&](const QColor& color)
                {
                    // update
                    properties.textColor = color;
                    DrawPreview();
                }
        );
        connect(textColorSelector.get(), &QColorDialog::colorSelected,
                [&](const QColor& color)
                {
                    // update, confirm, reset
                    properties.textColor = color;
                    confirmedProperties.textColor = color;
                    DrawPreview();
                    textColorSelector.reset();
                }
        );
    }
    textColorSelector->hide();
    textColorSelector->show();
}

void PropertiesWindow::onBackColorButtonPressed()
{
    if (! backColorSelector)
    {
        backColorSelector.reset(new QColorDialog());
        backColorSelector->setWindowTitle("Select Background Color");
        connect(backColorSelector.get(), &QColorDialog::rejected,
                [&]()
                {
                    // revert, reset
                    properties.backColor = confirmedProperties.backColor;
                    DrawPreview();
                    backColorSelector.reset();
                }
        );
        connect(backColorSelector.get(),&QColorDialog::currentColorChanged,
                [&](const QColor& color)
                {
                    // update
                    properties.backColor = color;
                    DrawPreview();
                }
        );
        connect(backColorSelector.get(), &QColorDialog::colorSelected,
                [&](const QColor& color)
                {
                    // update, confirm, reset
                    properties.backColor = color;
                    confirmedProperties.backColor = color;
                    DrawPreview();
                    backColorSelector.reset();
                }
        );
    }
    backColorSelector->hide();
    backColorSelector->show();
}

Properties PropertiesWindow::GetProperties()
{
    return confirmedProperties;
}

void PropertiesWindow::DrawPreview(void)
{
    QString textColorString = QString("color: rgb(%1, %2, %3);")
            .arg(properties.textColor.red())
            .arg(properties.textColor.green())
            .arg(properties.textColor.blue());
    QString backColorString = QString("background-color: rgb(%1, %2, %3);")
            .arg(properties.backColor.red())
            .arg(properties.backColor.green())
            .arg(properties.backColor.blue());
    QString styleSheetString = "QTextEdit {" + textColorString + backColorString + "}";
    ui->sampleText->setStyleSheet(styleSheetString);
    ui->sampleText->setText(ui->sampleText->toPlainText());
}

PropertiesWindow::~PropertiesWindow()
{
    delete ui;
}

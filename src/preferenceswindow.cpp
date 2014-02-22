#include "preferenceswindow.h"
#include "ui_preferenceswindow.h"

PreferencesWindow::PreferencesWindow(Properties prop, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesWindow),
    properties(prop)
{
    ui->setupUi(this);
    DrawPreview();
    connect(ui->textColorButton, &QPushButton::pressed,
            this, &PreferencesWindow::onTextColorButtonPressed);
    connect(ui->backColorButton, &QPushButton::pressed,
            this, &PreferencesWindow::onBackColorButtonPressed);
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
}
void PreferencesWindow::onTextColorButtonPressed()
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

void PreferencesWindow::onBackColorButtonPressed()
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

Properties PreferencesWindow::GetProperties()
{
    return confirmedProperties;
}

void PreferencesWindow::DrawPreview(void)
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

PreferencesWindow::~PreferencesWindow()
{
    delete ui;
}

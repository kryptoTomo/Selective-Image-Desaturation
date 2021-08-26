#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QResizeEvent>
#include <QMessageBox>
#include "options.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ImageOriginalPanel->setMinimumSize(1, 1);
    ui->ImageChangedPanel->setMinimumSize(1, 1);
    _desaturation = new DesatProcess;
}

MainWindow::~MainWindow()
{
    delete _desaturation;
    delete ui;
}
//odtworzenie pliku
void MainWindow::on_actionOpen_triggered()
{
    QString direction = QFileDialog::getOpenFileName(this,tr("Open Image"),"", tr("Image Files (*.jpg)"));
    if (direction.isEmpty())
        return;
    _original.load(direction);
    _relation = static_cast<float>(_original.height())/static_cast<float>(_original.width());
    _desaturation->load(_original);
    _desaturation->refresh();
    _relationPanel = static_cast<float>(ui->ImageChangedPanel->height())/static_cast<float>(ui->ImageChangedPanel->width());
    setImage();

}
//reakcja na zmiane rozmiaru okna
void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   if(_original.isNull())
       return;
   setImage();
}
//Ustawienie i wyświetlenie obrazu
void MainWindow::setImage()
{
    _relationPanel = static_cast<float>(ui->ImageChangedPanel->height())/static_cast<float>(ui->ImageChangedPanel->width());
    if(_relationPanel>_relation)
    {
        ui->ImageOriginalPanel->setPixmap(_original.scaledToWidth(ui->ImageOriginalPanel->width()));
        ui->ImageChangedPanel->setPixmap(_desaturation->getPixmap().scaledToWidth(ui->ImageChangedPanel->width()));
    }
    else
    {
        ui->ImageChangedPanel->setPixmap(_desaturation->getPixmap().scaledToHeight(ui->ImageOriginalPanel->height()));
        ui->ImageOriginalPanel->setPixmap(_original.scaledToHeight(ui->ImageChangedPanel->height()));
    }

}
void MainWindow::setImageChanged()
{
    if(_relationPanel>_relation)
    {
        ui->ImageChangedPanel->setPixmap(_desaturation->getPixmap().scaledToWidth(ui->ImageChangedPanel->width()));
    }
    else
    {
        ui->ImageChangedPanel->setPixmap(_desaturation->getPixmap().scaledToHeight(ui->ImageChangedPanel->height()));
    }

}
//zapisanie obrazu
void MainWindow::on_actionSave_triggered()
{
    if(_original.isNull())
    {
        QMessageBox error;
        error.setText(tr("The image has not been loaded!"));
        error.exec();
        return;
    }
    QString direction = QFileDialog::getSaveFileName(this,tr("Save Image"),tr("Desaturated Image"),tr("*.jpg"));
    if (direction.isEmpty())
        return;
    QFile file(direction);
    file.open(QIODevice::WriteOnly);
    _desaturation->getPixmap().save(&file);
}
//wyświetlenie okna opcji
void MainWindow::on_actionOptions_triggered()
{
    if(_original.isNull())
    {
        QMessageBox error;
        error.setText(tr("The image has not been loaded! Cannot open Settings"));
        error.exec();
        return;
    }
    Options opt(_desaturation,this);
    opt.setWindowTitle("Settings");
    opt.setModal(true);
    opt.exec();

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About",
                       "Selective Desaturation\nCreated by\nTomasz Madej\nJulia Bała\nDawid Wojdylak");
}


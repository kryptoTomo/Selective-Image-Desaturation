#include "options.h"
#include "ui_options.h"

Options::Options(DesatProcess * upd,MainWindow * m,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    _update=upd;
    _main=m;
    ui->treshold->setValue(_update->getTresh());
    ui->blur->setValue(_update->getBlur());
    ui->saturation->setValue(_update->getSat());
    ui->typeSat->setCurrentIndex(_update->getTypeSat());
}

Options::~Options()
{
    delete ui;
}



void Options::on_treshold_valueChanged(int value)
{
    _update->setTresh(value);
    _update->refresh();
    _main->setImageChanged();
}

void Options::on_saturation_valueChanged(int value)
{
    _update->setSat(value);
    _update->refresh();
    _main->setImageChanged();
}

void Options::on_blur_valueChanged(int value)
{
    _update->setBlur(value);
    _update->refresh();
    _main->setImageChanged();
}

void Options::on_close_clicked()
{
    this->close();
}

void Options::on_typeSat_activated(int index)
{
    if(index==0)
    {
        ui->treshold->setRange(0,255);
        ui->progressBar_2->setRange(0,255);
    }
    else if(index==1)
    {
       ui->treshold->setRange(0,359);
       ui->progressBar_2->setRange(0,359);
    }
    else if(index==2)
    {
        ui->treshold->setRange(0,255);
        ui->progressBar_2->setRange(0,255);
    }
    else if(index==3)
    {
        ui->treshold->setRange(0,255);
        ui->progressBar_2->setRange(0,255);
    }
    else if(index==4)
    {
        ui->treshold->setRange(0,255);
        ui->progressBar_2->setRange(0,255);
    }
    else if(index==5)
    {
        ui->treshold->setRange(0,255);
        ui->progressBar_2->setRange(0,255);
    }
    else if(index==6)
    {
        ui->treshold->setRange(0,255);
        ui->progressBar_2->setRange(0,255);
    }
    else if(index==7)
    {
        ui->treshold->setRange(0,255);
        ui->progressBar_2->setRange(0,255);
    }

    _update->setTypeSat(index);
    _update->refresh();
    _main->setImageChanged();
}

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include"desatprocess.h"
#include"mainwindow.h"
/* @brief - klasa reprezentująca okno ustawień
*/
namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(DesatProcess * upd,MainWindow * m,QWidget *parent=nullptr);
    ~Options();

private slots:
    /* @brief - reakcja na zmienienie wartości progu desaturacji
    */
    void on_treshold_valueChanged(int value);
    /* @brief - reakcja na zmiane poziomu desaturacji
    */
    void on_saturation_valueChanged(int value);
    /* @brief - reakcja na zmiane wartość rozmycia
    */
    void on_blur_valueChanged(int value);
    /* @brief - wyłącza okno ustawień
    */
    void on_close_clicked();
    /* @brief - reakcja na zmiane kryterium desaturacji
    */
    void on_typeSat_activated(int index);

private:
    DesatProcess * _update;
    Ui::Options *ui;
    MainWindow * _main;
};

#endif // OPTIONS_H

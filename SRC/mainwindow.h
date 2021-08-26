#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPixmap>
#include"desatprocess.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/* @brief - klasa reprezentująca główne okno aplikacji
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /* @brief - metoda uruchamiająca się na czynność zmianny rozmiaru okna, dostosowuje rozmiary obrazów
    */
    void resizeEvent(QResizeEvent* event);
    /* @brief - metoda wyswietlająca obrazy
    */
    void setImage();
    /* @brief - metoda wyswietlająca obraz zmieniony
    */
    void setImageChanged();
private slots:
    /* @brief - metoda otwiera okno wyboru obrazu
    */
    void on_actionOpen_triggered();
    /* @brief - zapisuje obraz zmieniony
    */
    void on_actionSave_triggered();
    /* @brief - otwiera okno ustawien
    */
    void on_actionOptions_triggered();
    /* @brief - wyświetla okno informacji o twórcach aplikacji
    */
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    /* @param _desaturation - obiekt zajmujący się procesem desaturacji
    */
    DesatProcess * _desaturation=nullptr;
    /* @param _original - orginalny obraz
    */
    QPixmap _original;
    /* @param _relation - relacja jednego boku do drugiego obrazu
    */
    float _relation;
    /* @param _relation - relacja jednego boku do drugiego panelu
    */
    float _relationPanel;

};
#endif // MAINWINDOW_H

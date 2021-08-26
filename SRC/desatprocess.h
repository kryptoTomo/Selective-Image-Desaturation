#ifndef DESATPROCESS_H
#define DESATPROCESS_H
#include<QImage>
#include<QPixmap>
/* @brief - klasa zajmująca się desaturacją obrazu na podstawie konktretnych kryterióW
*/
class DesatProcess
{
public:
    /* @brief - konstruktor domyślny
    */
    DesatProcess();
    /* @brief - metoda wczytująca obraz
     * @param buffer - obraz który zostanie wczytany
    */
    void load(QPixmap buffer);
    /* @brief - metoda która odświerza i przeprowadza desaturacje
    */
    void refresh();
    /* @brief - zwraca obraz po desaturacji
    */
    QPixmap getPixmap()const;
    /* @brief - metoda ustawiająca wartość(próg desaturacji)
     * @param val - próg desaturacji
    */
    void setTresh(int val);
    /* @brief - metoda ustawiająca  wartość rozmycia
     * @param val - wartość rozmycia
    */
    void setBlur(int val);
    /* @brief - metoda ustawiająca wartość saturacji w [%]
     * @param val - wartość saturacji
    */
    void setSat(int val);
    /* @brief - metoda ustawiająca kryterium desaturacji
     * @param val - kryterium desaturacji
    */
    void setTypeSat(int val);
    /* @return - zwraca parametr próg desaturacji
    */
    int getTresh()const;
    /* @return - zwraca parametr rozmycia
    */
    int getBlur()const;
    /* @return - zwraca parametr saturacji
    */
    int getSat()const;
    /* @return - zwraca parametr kryterium desaturacji
    */
    int getTypeSat()const;
private:
    /* @param _treshold - próg desaturacji
    */
    int _treshold=0;
    /* @param _blur - rozmycie
    */
    int _blur=0;
    /* @param _saturation poziom desaturacji
    */
    int _saturation=0;
    /* @param _typeSat - kryterium desaturacji
    */
    int _typeSat=0;
    /* @param _orginal - przechowuje orginalny obraz
    */
    QImage _original;
    /* @param _changed - przechowuje obraz po desaturacji
    */
    QImage _changed;
    /* @return - najmniejszą wartość składowa kolorów rgb
    */
    int minCol(const int & red,const int & green,const int &  blue)const;
    /* @return - największa wartość składowa kolorów rgb
    */
    int maxCol(const int & red,const int & green,const int &  blue,bool cmy = false,const int &  dark=0)const;
    /* @return - środkową wartość składowa kolorów rgb
    */
    int midCol(const QColor & col)const;
    /* @brief - metoda przygotowująca parametr temp do desaturacji na podstawie jasności
    */
    void lightness(const QColor & col,int & min,int &max,int & temp)const;
    /* @brief - metoda przygotowująca parametr temp do desaturacji na podstawie wartości parametru hue
    */
    void hue(const QColor & col,int & min,int &max,int & temp)const;
    /* @brief - metoda wyliczająca kąt koloru na kole barw, do wyliczenia hue
    */
    int checkAngle(const QColor & col,const int &max,const int & min)const;
    /* @brief - metoda przygotowująca parametr temp do desaturacji na podstawie składowej R
    */
    QColor partlyDesaturation(const int & red,const int & green,const int &  blue,const int & max,bool cmy = false,const int &  dark=0);

    QColor blurDesaturation(const int & red,const int & green,const int &  blue, const int & max,const int & delta,bool cmy = false,const int &  dark=0);
};

#endif // DESATPROCESS_H

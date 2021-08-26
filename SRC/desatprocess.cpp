#include "desatprocess.h"
#include <QColor>

DesatProcess::DesatProcess()
{

}
void DesatProcess::load(QPixmap buffer)
{
    _original=buffer.toImage();
    _changed=_original;
}
QPixmap DesatProcess::getPixmap()const
{
    return QPixmap::fromImage(_changed);
}
void DesatProcess::refresh()
{
    int height = _original.height();
    int width = _original.width();
    _changed = _original;
    int temp = 0;
    int min = 0;
    int max;
    int delta = 0;
    QColor col;
    if(_typeSat<5)//dla RGB
    {
        for (int i = 0; i < width; i++)
            for(int j = 0;j<height;j++)
            {

                col= _original.pixelColor(i,j);
                max = maxCol(col.red(),col.green(),col.blue());
                switch(_typeSat)
                {
                case 0:
                    lightness(col,min,max,temp);
                    break;
                case 1:
                    hue(col,min,max,temp);
                    break;
                case 2:
                    temp = col.red();
                    break;
                case 3:
                    temp = col.green();
                    break;
                case 4:
                    temp = col.blue();
                    break;
                default:
                    return;

                }

                if (temp < (_treshold - _blur))
                {

                    if (max < 0)
                        max = 0;
                    _changed.setPixelColor(i,j,partlyDesaturation(col.red(),col.green(),col.blue(),max));
                }

                else if ((temp > _treshold - _blur) && (temp < _treshold))
                {
                    delta = _treshold - temp;
                    _changed.setPixelColor(i,j,blurDesaturation(col.red(),col.green(),col.blue(), max,delta).toRgb());
                }
        }
    }
    else //Dla CMY
    {
        for (int i = 0; i < width; i++)
            for(int j = 0;j<height;j++)
            {

                col= _original.pixelColor(i,j).toCmyk();
                max = maxCol(col.cyan(),col.magenta(),col.yellow(),true,col.black());
                switch(_typeSat)
                {
                case 5:
                    temp = col.cyan();
                    break;
                case 6:
                    temp = col.magenta();
                    break;
                case 7:
                    temp = col.yellow();
                    break;
                default:
                    return;

                }

                if (temp < (_treshold - _blur))
                {

                    if (max < 0)
                        max = 0;
                    _changed.setPixelColor(i,j,partlyDesaturation(col.cyan(),col.magenta(),col.yellow(), max,true,col.black()));
                }
                else if ((temp > _treshold - _blur) && (temp < _treshold))
                {
                    delta = _treshold - temp;
                    delta = _saturation + delta;
                    if (delta > 100)
                        delta = 100;
                    _changed.setPixelColor(i,j,blurDesaturation(col.cyan(),col.magenta(),col.yellow(), max,delta,true,col.black()));
                }
            }
    }

}

QColor DesatProcess::partlyDesaturation(const int & red,const int & green,const int &  blue,const int & max,bool cmy,const int &  dark)
{
    double deltaR, deltaG, deltaB;
    deltaR = static_cast<double>(max) - static_cast<double>(red);
    deltaG = static_cast<double>(max) - static_cast<double>(green);
    deltaB = static_cast<double>(max) - static_cast<double>(blue);

    deltaR = deltaR * (1.0 - (static_cast<double>(_saturation) / 100.0));
    deltaG = deltaG * (1.0 - (static_cast<double>(_saturation) / 100.0));
    deltaB = deltaB * (1.0 - (static_cast<double>(_saturation) / 100.0));
    if(cmy)
    {
        double deltaD = static_cast<double>(max) - static_cast<double>(dark);
        deltaD = deltaD * (1.0 - (static_cast<double>(_saturation) / 100.0));
        QColor x;
        x.toCmyk();
        x.setCmyk(red+static_cast<int>(deltaR),green+ static_cast<int>(deltaG),blue+ static_cast<int>(deltaB),dark+ static_cast<int>(deltaD));
        return x.toRgb();
    }
    else
        return QColor(red+static_cast<int>(deltaR),green+ static_cast<int>(deltaG),blue+ static_cast<int>(deltaB));
}
QColor DesatProcess::blurDesaturation(const int & red,const int & green,const int &  blue, const int & max,const int & delta,bool cmy,const int &  dark)
{
    double deltaR, deltaG, deltaB;
    deltaR = static_cast<double>(max) - static_cast<double>(red);
    deltaG = static_cast<double>(max) - static_cast<double>(green);
    deltaB = static_cast<double>(max) - static_cast<double>(blue);

    deltaR = deltaR * (1.0 - (static_cast<double>(_saturation) / 100.0));
    deltaG = deltaG * (1.0 - (static_cast<double>(_saturation) / 100.0));
    deltaB = deltaB * (1.0 - (static_cast<double>(_saturation) / 100.0));

    if (deltaR > 0.)
        deltaR = deltaR * (1.0 - (static_cast<double>(delta)) / static_cast<double>(_blur));

    if (deltaG > 0.)
        deltaG = deltaG * (1.0 - (static_cast<double>(delta)) / static_cast<double>(_blur));

    if (deltaB > 0.)
        deltaB = deltaB * (1.0 - (static_cast<double>(delta)) / static_cast<double>(_blur));
    if(cmy)
    {
        double deltaD = static_cast<double>(max) - static_cast<double>(dark);
        deltaD = deltaD * (1.0 - (static_cast<double>(_saturation) / 100.0));
        if (deltaD > 0.)
            deltaD = deltaD * (1.0 - (static_cast<double>(delta)) / static_cast<double>(_blur));
        QColor x;
        x.toCmyk();
        x.setCmyk(red+static_cast<int>(deltaR),green+ static_cast<int>(deltaG),blue+ static_cast<int>(deltaB),dark+ static_cast<int>(deltaD));
        return x.toRgb();
    }
    else
        return QColor(red+static_cast<int>(deltaR),green+ static_cast<int>(deltaG),blue+ static_cast<int>(deltaB));

}
void DesatProcess::lightness(const QColor & col,int & min,int &max,int & temp)const
{
    min = minCol(col.red(),col.green(),col.blue());
    temp = (max + min) / 2;
}
void DesatProcess::hue(const QColor & col,int & min,int &max,int & temp)const
{
    int angle, mid;

    temp = 0;
    mid = midCol(col);
    min = minCol(col.red(),col.green(),col.blue());

    angle = checkAngle(col,max,min);
    if (max != min)
        temp = static_cast<int>((mid - min) / (max - min) * 60) + angle;

}

int DesatProcess::checkAngle(const QColor & col,const int &max,const int & min)const
{
    int angle = 0;
    if ((col.red() == max) && (col.blue() == min)) {
        angle = 0;
    }
    else if ((col.green() == max) && (col.blue() == min)) {
        angle = 60;
    }
    else if ((col.green() == max) && (col.red() == min)) {
        angle = 120;
    }
    else if ((col.blue() == max) && (col.red() == min)) {
        angle = 180;
    }
    else if ((col.blue() == max) && (col.green() == min)) {
        angle = 240;
    }
    else if ((col.red() == max) && (col.green() == min)) {
        angle = 300;
    }


    return angle;
}

int DesatProcess::minCol(const int & red,const int & green,const int &  blue)const
{
    int min;
    if (red < green)
        if (red < blue)
            min = red;
        else
            min = blue;
    else
        if (green < blue)
            min = green;
        else
            min = blue;
    return min;
}
int DesatProcess::midCol(const QColor & col)const
{
    int min, mid, max;
    min = minCol(col.red(),col.green(),col.blue());
    max = maxCol(col.red(),col.green(),col.blue());

    if (col.red() == min) {
        if (col.green() == max) {
            mid = col.blue();
        }
        else {
            mid = col.green();
        }
    }
    else if (col.green() == min) {
        if (col.red() == max) {
            mid = col.blue();
        }
        else {
            mid = col.red();
        }
    }
    else {
        if (col.green() == max) {
            mid = col.red();
        }
        else {
            mid = col.green();
        }
    }

    return mid;
}
int DesatProcess::maxCol(const int & red,const int & green,const int &  blue,bool cmy,const int &  dark)const
{
    int max;
    if (red > green)
        if (red > blue)
            max = red;
        else
            max = blue;
    else
        if (green > blue)
            max = green;
        else
            max = blue;
    if(cmy)
        if(dark>max)
            max = dark;
    return max;
}

int DesatProcess::getTresh()const
{
    return _treshold;
}
int DesatProcess::getBlur()const
{
    return _blur;
}
int DesatProcess::getSat()const
{
    return _saturation;
}
int DesatProcess::getTypeSat()const
{
   return _typeSat;
}
void DesatProcess::setTresh(int val)
{
   _treshold=val;
}
void DesatProcess::setBlur(int val)
{
    _blur=val;
}
void DesatProcess::setSat(int val)
{
    _saturation=val;
}
void DesatProcess::setTypeSat(int val)
{
    _typeSat=val;
}



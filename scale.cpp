#include <scale.h>

//default constructor
Scale::Scale():
    XScale(1),
    YScale(1),
    win_x(0),
    win_y(0),
    flag_t(keep_ratio),
    pos_x(0),
    pos_y(0)
{

}
//constructor - grabs size of displaying window in pixels
Scale::Scale(unsigned int frame_x,unsigned int frame_y) :
    XScale(1),
    YScale(1),
    win_x(frame_x),
    win_y(frame_y),
    flag_t(keep_ratio),
    pos_x(0),
    pos_y(0)
{


}




Scale::~Scale()
{
    std::cout<<"Scale obj destroyed\n";
}

void Scale::adjust(const unsigned int x,const unsigned int y,bool center,mode arg)
{
    if(win_x==0 || win_y==0)
    {
        std::cout<<"win_x and/or win_y are NOT set!\n";
        return;
    }
    setX(x);
    setY(y);
    setMode(arg);

    calculate(arg);
    std::cout<<"Adjusted scale "<<XScale<<" "<<YScale<<"\n";

    setPosition(center);

}

void Scale::adjust(bool center)
{
    if(win_x==0 || win_y==0)
    {
        std::cout<<"win_x and/or win_y are NOT set!\n";
        return;

    }

    calculate(flag_t);
    std::cout<<"Adjusted scale "<<XScale<<" "<<YScale<<"\n";

    setPosition(center);


}

float Scale::getXScale()
{
    return XScale;
}

float Scale::getYScale()
{
    return YScale;
}

void Scale::setMode(mode arg)
{
    flag_t=arg;
}

void Scale::setX(unsigned int x)
{
    img_x=x;
}
void Scale::setY(unsigned int y)
{
    img_y=y;
}

void Scale::setframeX(unsigned int x)
{
  win_x=x;
}

void Scale::setframeY(unsigned int y)
{
  win_y=y;
}


void Scale::setPosition(bool center)
{
    if(center)
    {
        pos_x=(win_x-img_x*XScale)/2;
        pos_y=(win_y-img_y*YScale)/2;
    }
    else
    {
        pos_x=0;
        pos_y=0;
    }

}

unsigned int Scale::getPosX()
{
    return pos_x;
}

unsigned int Scale::getPosY()
{
    return pos_y;
}

void Scale::calculate(mode arg)
{
    switch (arg)
    {
    case keep_ratio:
        XScale=(win_x>img_x? 1 : float(win_x)/img_x);
        YScale=(win_y>img_y? 1 : float(win_y)/img_y);
        XScale>YScale? XScale=YScale : YScale=XScale;
        break;

    case fit_to_screen:
        XScale=(win_x>img_x? 1 : float(win_x)/img_x);
        YScale=(win_y>img_y? 1 : float(win_y)/img_y);
        break;
    case stretch_and_keep_ratio:
        XScale=(img_x>win_x? float(img_x)/win_x : float(win_x)/img_x);
        YScale=(img_y>win_y? float(img_y)/win_y : float(win_y)/img_y);
        XScale>YScale? XScale=YScale : YScale=XScale;
        break;
    case stretch_to_fit:
        XScale=(img_x>win_x? float(img_x)/win_x : float(win_x)/img_x);
        YScale=(img_y>win_y? float(img_y)/win_y : float(win_y)/img_y);
        break;

    }
}

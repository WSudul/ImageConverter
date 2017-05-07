#include "vec_extr.h"
#include <qDebug>
//implementacja funkcji img_extract
std::vector<uint8_t> Vec_Extr::img_extract(sf::Image & image,ImgBaseInfo &info,color_mode flag)
{

    std::vector<uint8_t> Vec;

    extract(Vec,image,info,flag);

    return Vec;
}

//Przeladowanie funkcji img_extract wykorzystujace string
std::vector<uint8_t> Vec_Extr::img_extract(std::string file,ImgBaseInfo &info,color_mode flag)
{
    sf::Image image;

    std::vector<uint8_t> Vec;

    if(!image.loadFromFile(file))
    {
        std::cout<<"Fail\n";

    }
    else
        extract(Vec,image,info,flag);

    return Vec;
}


void Vec_Extr::extract(std::vector<uint8_t>& Vec,sf::Image &image,ImgBaseInfo &info,color_mode flag)
{
    sf::Color pixel;
    sf::Vector2u Size=image.getSize();
    info.size.x=Size.x;
    info.size.y=Size.y;

    //wybor odpowiedniej opcji
    switch(flag)
    {
    //![VEC_EXTR COLOR_MODE EXAMPLE]
    case RGBA:
        info.model=ImgBaseInfo::RGBA;
    //![VEC_EXTR COLOR_MODE EXAMPLE]
        Vec.reserve(Size.x*Size.y*4);
        for(long long y=Size.y-1;y>=0;--y)
        {

            for(long long x=0;x<Size.x;x++)
            {
                pixel=image.getPixel(x,y);


                Vec.push_back(pixel.b);
                Vec.push_back(pixel.g);
                Vec.push_back(pixel.r);
                Vec.push_back(pixel.a);
            }
        }
        break;
    case RGB:
        info.model=ImgBaseInfo::RGB;
        Vec.reserve(Size.x*Size.y*3);
        for(long long y=Size.y-1;y>=0;--y)
        {

            for(long long x=0;x<Size.x;x++)
            {
                pixel=image.getPixel(x,y);
                Vec.push_back(pixel.b);
                Vec.push_back(pixel.g);
                Vec.push_back(pixel.r);
            }
        }
        break;
    case GREYSCALE:
        info.model=ImgBaseInfo::GREY;
        Vec.reserve(Size.x*Size.y);
        for(long long y=Size.y-1;y>=0;--y)
        {

            for(long long x=0;x<Size.x;x++)
            {
                pixel=image.getPixel(x,y);
                Vec.push_back(pixel.r*0.21+pixel.g*0.72+pixel.b+0.007);
            }
        }
        break;
    case GREYSCALE_AVG:
        info.model=ImgBaseInfo::GREY;
        Vec.reserve(Size.x*Size.y);
        for(long long y=Size.y-1;y>=0;--y)
        {

            for(long long x=0;x<Size.x;x++)
            {
                pixel=image.getPixel(x,y);
                Vec.push_back((pixel.r+pixel.g+pixel.b)/3);
            }
        }
        break;
    case inverted_RGB:
        info.model=ImgBaseInfo::RGB;
        Vec.reserve(Size.x*Size.y*4);
        for(long long y=0;y<Size.y;y++)
        {

            for(long long x=0;x<Size.x;x++)
            {
                pixel=image.getPixel(x,y);
                Vec.push_back(255-pixel.b);
                Vec.push_back(255-pixel.g);
                Vec.push_back(255-pixel.r);

            }
        }
        break;

    }

};

//pakowanie wektora do wielokrotnosci 32bitow w rzedzie
std::vector<uint8_t> Vec_Extr::PackVectorTo32Bit(std::vector<uint8_t> &vector,int32_t w,int32_t h,color_mode flag)
{   qDebug()<<"Start";
    int pix_size; // ilosc bajtow przypadajacych na 1 piksel
    //wybor odpowiedniej opcji
    switch(flag)
    {
    case RGBA:
        pix_size=4;
        break;
    case RGB:
        pix_size=3;
        break;
    case GREYSCALE:
        pix_size=1;
        break;
    default:
        //niewspierana flaga
        return std::vector<uint8_t>();
    }

    qDebug()<<"przed testem na vector.size";
    if(vector.size()!=(uint32_t(pix_size*w*h)))
        return std::vector<uint8_t>();
    qDebug()<<"po tescie na vector size";
    int pad=0;
    if((w*pix_size)%4 !=0)
        pad=4-((w * pix_size) % 4);

    qDebug()<<"\tpad="<<pad;
    if(pad==0)
        return vector;

    //wektor dla wartosci z paddingiem
    std::vector<uint8_t> vec_padded;

    vec_padded.resize((w*pix_size+pad)*h);

     qDebug()<<"vec_padded size="<<vec_padded.size();
    //iteratory dla elementow wektora wejsciowego
    std::vector<uint8_t>::iterator it_row_start=vector.begin();
    std::vector<uint8_t>::iterator it_row_end=vector.begin()+w*pix_size;
     qDebug()<<std::distance(it_row_start,it_row_end);
    //int i=0;
    //petla kopiujaca w elementow do nowego wektora, a nastpenie wstawiajaca wyzerowane elementy jako padding
    for(std::vector<uint8_t>::iterator it = vec_padded.begin(); it != vec_padded.end(); it=it+pad)
    {
        std::copy(it_row_start,it_row_end,it);
        std::advance(it,w*pix_size);
        //qDebug()<<++i;
        std::advance(it_row_start,w*pix_size);
        std::advance(it_row_end,w*pix_size);

        for(std::vector<uint8_t>::iterator it_p=it;it_p!=it+pad;it_p++)
        {
             *it_p=0;

        }
    }

    return vec_padded;
}

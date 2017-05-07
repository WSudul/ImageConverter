#include "vec_bmp.h"
#include <QDebug>
#define _32BIT 4
#define _24BIT 3
#define _8BIT 1

Vec_BMP::Vec_BMP()
{

}

//zapisanie wektora do 24bitmapy
bool Vec_BMP::SaveTo24BMP(const std::string& file,const std::vector<uint8_t>& vector, int32_t w, int32_t h) {


    //utworzenie struktruy i przypisanie jej wartosci
    BITMAPINFOHEADER bmpih;

    bmpih.biSize = sizeof(BITMAPINFOHEADER);
    bmpih.biWidth = w;
    bmpih.biHeight = h;
    bmpih.biPlanes = 1;
    bmpih.biBitCount = _24BIT*8;
    bmpih.biCompression = A_BI_RGB;
    bmpih.biXPelsPerMeter=3779; //96 dpi
    bmpih.biYPelsPerMeter=3779; //96 dpi
    bmpih.biClrUsed=0;
    bmpih.biClrImportant=0;

    //bledne wartosci w lub h
    if(w<1 || h<1)
        return false;

    //ustalanie wartosci paddingu
    int pad = 0;
    if((w*_24BIT)%4 !=0)
        pad=4-((w * _24BIT) % 4);

    bmpih.biSizeImage=(w*_24BIT+pad)*h;
    qDebug()<<"\t\t pad="<<pad;

    //gdy wektor ma inny rozmiar od obliczonego rozmiaru
    if(vector.size()!=bmpih.biSizeImage)
        return false;


    //utworzenie pliku
    std::ofstream pFile(file, std::ios_base::binary);
    if (!pFile.is_open())
    {
        return false;
    }

    //druga struktura
    BITMAPFILEHEADER bmpfh;

    int nBitsOffset = sizeof(BITMAPFILEHEADER) + bmpih.biSize;
    LONG lImageSize = bmpih.biSizeImage;
    LONG lFileSize = nBitsOffset + lImageSize;
    bmpfh.bfType = 'B' + ('M' << 8);
    bmpfh.bfOffBits = nBitsOffset;
    bmpfh.bfSize = lFileSize;
    bmpfh.bfReserved1 = bmpfh.bfReserved2 = 0;


    // file header do pliku
    pFile.write((const char*)&bmpfh, sizeof(BITMAPFILEHEADER));


    // info header do pliku
    pFile.write((const char*)&bmpih, sizeof(BITMAPINFOHEADER));
    ;

    //zawartosc wektora do pliku
    pFile.write((const char*)&vector[0], vector.size());

    pFile.close();

    return true;
}



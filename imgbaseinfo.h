#ifndef IMGBASEINFO_H
#define IMGBASEINFO_H

#include <string>

class ImgBaseInfo
{
    /*! \class ImgBaseInfo imgbaseinfo.h
     *  \brief Przechowywanie informacji o przetwrzonym obrazie przez Vec_Extr
     *
     *  Klasa ma za zadanie przechowywac wylacznie informacje na temat wybranego sposobu zczytania i formatowania danych przez
     *  metody uzyte w klasie Vec_Extr
     *
     */
public:
    struct unsigned_pair /*! struktura przechowywujaca rozmiary obrazu */
    {
        uint32_t x; /*! <szerokosc w pikselach */
        uint32_t y; /*! <wysokosc w pikselach */
    };

    //! [IMGBASEINFO DATA_MODEL]
    /*! Enum odpowiedzialny za przydzielenie odpowiedniego formatu przechowywanych danych.
        \n Ustalany na podstawie wybranej wartosci enum z Vec_Extr ,np:
        \snippet vec_extr.cpp VEC_EXTR COLOR_MODE EXAMPLE

        \warning \n Przy modyfikacji zawartosci enum data_model nalezy uwzglednic enum Vec_Extr::color_mode
        \snippet vec_extr.h VEC_EXTR COLOR_MODE
        */
    enum data_model
    {
        RGB,        /*!< pixel jako 3  bajty R,G,B */
        RGBA,       /*!< pixel jako 4  bajty R,G,B,A */
        GREY,       /*!< pixel jako 1 bajt */
        BLACK_WHITE,/*!< dane jako wartosc 1 wartosc (0/1) */
        HSV,        /*!< dane jako 3 wartosci H,S,V */
        CMY,        /*!< dane jako 3 wartosci C,M,Y */
        CMYK        /*!< dane jako 4 wartosci C,M,Y,K */
    };
    //! [IMGBASEINFO DATA_MODEL]


    unsigned_pair size; /*!< struktura przechowywujaca wymiary obrazu */
    data_model model;   /*!< enum przechowywujacy informacje na temat typu przechowywanych danych */
};

#endif // IMGBASEINFO_H

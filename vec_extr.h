#ifndef VEC_EXTR_H
#define VEC_EXTR_H

#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgbaseinfo.h>
#include <vec_bmp.h>
#include <iterator>

class Vec_Extr: public Vec_BMP
{
    /*! \class Vec_Extr vec_extr.h
     *  \brief Wydobywanie pikseli z obiektu sf::image
     *
     *  Klasa odpowiedzialna za wyciagniecie pikseli w pewnym okreslonym formacie
     *
     *
     *
     *  Klasa Vec_Extr wymaga obecnosci biblioteki imgbaseinfo.h, ktora zawiera obiekt do ktorego poprzez referencje
     *  zostaja zwrocone informacje o obrazie.
     *  Klasa dziedziczy po Vec_BMP metody zapisu wektora do bitmapy.
     *
     *  Wykorzystywana sa statyczne metody img_extract, która zwracaja
     *  pixele od dolnego lewego rogu, inkrementujac rzedy w gore w kolejnosci odwrotnej RGBA (ABGR).
     *  \n Metody img_extract są obudowami dla prywatnej metody void extract() wykonujacej zczytanie informacji z obrazu.
     *
     */
public:

    Vec_Extr();
    ~Vec_Extr();
    //![VEC_EXTR COLOR_MODE]
    //!
    /*! \enum color_mode - Ustawienie  odpowiedniego trybu
        \brief Enum, na podstawie ktorego zostaje wybrany odpowiedni tryb eksportu danych.
        \warning Metoda uzywajaca ten enum musi uwzgledniac kompatybilnosc z enum opisanym w ImgBaseInfo
        \snippet imgbaseinfo.h IMGBASEINFO DATA_MODEL
        \code{.cpp}
         //przyklad uzycia
         ImgBaseInfo info; //zawiera zmienna data_model info
         ...
            case RGBA:
                info.model=ImgBaseInfo::RGBA;
         \endcode
                        */
    enum color_mode
    {
        inverted_RGB,         /*!< odwrocona skala RGB == ImgBaseInfo::RGB*/
        GREYSCALE,      /*!< skala szarosci ==ImgBaseInfo::GREY */
        GREYSCALE_AVG,  /*!< skal szarosci na podstawie sredniej arytmetycznej ==ImgBaseInfo::GREY */
        RGB,            /*!< brak kanalu alpha (RGB) ==ImgBaseInfo::RGB */
        RGBA            /*!< brak zmian == (RGBA) ==ImgBaseInfo::RGBA */
    };
    //![VEC_EXTR COLOR_MODE]



    /*! \brief img_extract - wyciaganie danych o pixelach z obiektu sf::Image
     *
     *
     *  Obiekt Image jest przekazywany poprzez referencje
     *  Ta wersja img_extract zwraca wektor typu uint8_t
     *  \param [in] image – obiekt sf::Image,z ktorego pobierane sa dane
     *  \param [in] info - do obiektu zwracane sa podstawowe informacje zdefiniowane w ImgBaseInfo
     *  \param [in] flag – tryb pracy okreslany za pomoca typu enum color_mode
     *
     */
    static std::vector<uint8_t> img_extract(sf::Image & image,ImgBaseInfo& info,color_mode flag=RGBA);

    /*! \brief img_extract - wyciaganie danych o pixelach z obiektu sf::Image na podstawie sciezki i nazwy do pliku
     *
     *
     *  std::string przekazywany do funkcji
     *  Ta wersja img_extract zwraca wektor typu uint8_t
     *  \param [in] name – std::string bedacy sciezka i nazwa pliku
     *  \param [in] info - do obiektu zwracane sa podstawowe informacje zdefiniowane w ImgBaseInfo
     *  \param [in] flag – tryb pracy okreslany za pomoca typu enum color_mode
     *
     */
    static std::vector<uint8_t> img_extract(std::string name,ImgBaseInfo& info,color_mode flag=RGBA);

    /*! \brief Zapisanie wektora do 24-bitowej bitmapy
         *
         *  \param [in] vector - wektor z danymi
         *  \param [in] w - szerokosc w pikselach
         *  \param [in] h - wysokosc w pikselach
         *  \param [in] flag - enum, na podstawie ktorego wybrane zostanie odpowiedni dobor paddingu
         *
         *  Metoda zwracajaca nowy wektor danych, w ktorym dodano padding (do 32bit) na podstawie
         *  szerokosci obrazu w pikselach.
         *  W przypadku, gdy wektor wejsciowy jest pusty lub nie wymaga paddingu, to zostanie zwrocona
         *  kopia wejsciowego wektora. W przypadku wyboru niewspieranej opcji na podstawie dostepnych opcji
         *  metoda zwroci rowniez pusty wektor.
         *
         *  argument flag przyjmujac wartosc
         *  | flag      | bpp     |
         *  | :---:     | :----:  |
         *  | RGBA      | 32      |
         *  | RGB       | 24      |
         *  | GREYSCALE | 1       |
         *
         *
         *
         */
    std::vector<uint8_t> static PackVectorTo32Bit(std::vector<uint8_t> &vector,int32_t w,int32_t h,color_mode flag=RGBA);

private:

    /*! \brief extract - metoda pomocniczna ekstrakcji do wektora
     *
     *
     *  Wywolywana przez kazde przeladowanie metody img_extract.
     *  Obiekty sf::Image i std::vector musza byc przekazane przez referencje
     *  Wynik dzialania programu zostaje przekazany do wektora
     *  Ta wersja img_extract modyfikuje wektor typu uint8_t
     *  \param [in,out] Vec - wektor zawierajacy wynik
     *  \param [in] image – obiekt sf::Image,z ktorego pobierane sa dane
     *  \param [in] info - do obiektu zwracane sa podstawowe informacje zdefiniowane w ImgBaseInfo
     *  \param [in] flag – tryb pracy okreslany za pomoca typu enum color_mode
     *
     *
     */
    static void extract(std::vector<uint8_t>&Vec,sf::Image &image,ImgBaseInfo &info,color_mode flag);



};

#endif // VEC_EXTR_H

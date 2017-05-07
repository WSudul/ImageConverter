#ifndef VEC_BMP_H
#define VEC_BMP_H


#define BYTE uint8_t
#define WORD uint16_t
#define DWORD uint32_t
#define LONG int32_t

#define A_BI_RGB 0l
#define A_BI_RLE8 1l
#define A_BI_RLE4 2l
#define A_BI_BITFIELDS 3l
#define A_BI_JPEG 4l
#define A_BI_PNG 5l


#include <vector>
#include <string>
#include <fstream>
class Vec_BMP
{
public:
    Vec_BMP();
    /*! \class Vec_BMP vec_bmp.h
     *  \brief Klasa odpowiedzialna za zapisywanie danych do bitmapy
     *
     *
     *
     * Celem klasy jest zebranie metod zapisu danych zawartych w wektorze do bitmapy.
     * Zaimplementowane zostaly nastepujace metody statyczne:
     * - SaveTo24BMP
     * - PackVector
     *
     * do zapisu implementacja naglowka BITMAPINFOHEADER (rozmiar 40 bit) oraz BITMAPFILEHEADER (14 bit).
     * W celu unikniecia wykorzystania biblioteki windows.h zostaly one zaimplementowane wewnatrz klasy.
     * Z racji wykorzystania tylko tego naglowka, mozliwa jest kompatybilnosc z prawie wszystkimi programami
     * graficznymi.
     * Specyfikacja dotyczaca formatu na stronie MS:
     * -<a href="https://msdn.microsoft.com/en-us/library/windows/desktop/dd183391(v=vs.85).aspx">format .bmp</a>
     * -<a href="https://msdn.microsoft.com/en-us/library/windows/desktop/dd183374(v=vs.85).aspx">BITMAPFILEHEADER</a>
     * -<a href="https://msdn.microsoft.com/en-us/library/windows/desktop/dd183376(v=vs.85).aspx">BITMAPINFOHEADER</a>
     *
     *
     */


    /*! \brief Zapisanie wektora do 24-bitowej bitmapy
     *
     *  \param [in] file - plik do ktorego ma zostac zapisana  bitmapa
     *  \param [in] vector - wektor z danymi w formacie RGB
     *  \param [in] w - szerokosc w pikselach
     *  \param [in] h - wysokosc w pikselach
     *
     *  Metoda w przypadku sukcesu zwraca true. W przypadku, gdy ktorys argumentow metody bedzie niepoprawny, funkcja
     *  przerwie swoje dzialanie i zwroci wartosc false.
     *  Metoda tworzy nowy plik, do ktorego zostaja zapisane informacje w postaci binarnej. Na poczatku, zgodnie z standardem
     *  zostaja zapisane struktury informujace o parametrach pliku, a nastepnie dane z wektora.
     *  \n \warning Metoda wymaga, by dane byly przygotowane w odpowiednim formacie (tj zgodnie z odczytem, czyli zaczynajac od ostaniego rzedu)
     *  Obecny musi byc padding w wektorze. Aby zapewnic kompatybilnosc, przed wykonaniem tej metody, nalezy wykonac metode Vec_Extr::PackVector().
     *
     *
     *
     */
    static bool SaveTo24BMP(const std::string& file,const std::vector<uint8_t>& vector, int32_t w, int32_t h);



    /*!
     *
     *  \struct BITMAPFILEHEADER vec_bmp.h
     *
     *  \brief struktura zgodna z odpowiednikiem z windows.h
     *
     * Struktura reprezentujaca bitmapfileheader w typowej bitmapie.
     *
     *  Zostaje upakowana przy uzyciu:
     *  \code{.cpp}
     *      pragma pack(push,2)
     *  \endcode
     *  Dzieki czemu rozmiar wynosi dokladnie 14  bitow.
     */
    #pragma pack(push,2)
    struct BITMAPFILEHEADER
    {
        WORD  bfType;
        DWORD bfSize;
        WORD  bfReserved1;
        WORD  bfReserved2;
        DWORD bfOffBits;
    };
    #pragma pack(pop)


    /*!
     *
     *  \struct BITMAPINFOHEADER vec_bmp.h
     *
     *  \brief struktura zgodna z odpowiednikiem z windows.h
     *
     *  Struktura reprezentujaca bitmapinfoheader o rozmiarze 40 bitow zawierajaca dane o przechowywanym obrazie.
     *
    */
    struct BITMAPINFOHEADER
    {
        DWORD biSize;
        LONG  biWidth;
        LONG  biHeight;
        WORD  biPlanes;
        WORD  biBitCount;
        DWORD biCompression;
        DWORD biSizeImage;
        LONG  biXPelsPerMeter;
        LONG  biYPelsPerMeter;
        DWORD biClrUsed;
        DWORD biClrImportant;
    };



};

#endif // VEC_BMP_H

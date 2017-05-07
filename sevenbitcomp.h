#ifndef SEVENBITCOMP_H
#define SEVENBITCOMP_H

#include <vector>
#include <stdint.h>


class SevenBitComp
{
    /*! \class SevenBitComp sevenbitcomp.h
     *  \brief Kompresja/dekompresja stratna - z kazdego bajtu usuwany najmniej znaczacy bit
     *
     *  Klasa sluzy do kompresji stratnej danych z vectora i ich ponownej dekompresji;
     *  Operacje przeprowadzane sa na vektorach danych typu uint8_t
     *
     */


    public:

        SevenBitComp();

        ~SevenBitComp();

        //std::vector< uint8_t > compressedData;


    /*! \brief compress - kompresja danych z std::vector< uint8_t > Vec
     *
     *  Obiekty Vec i compressedData sa przekazywane poprzez referencje
     *  Kompresja jest stratna - tracony jest najmniej znaczacy bit w kazdym bajcie danych wejsciowych
     *  Nastepnie bity sa laczone po 8 i pakowane do vektora compressedData
     *
     *  \param [in] Vec – vektor danych wejsciowyh
     *  \param [out] compressedData - vektor, w ktorym zostaja zapisane skompresowane dane
     *
     */
        void compress(std::vector< uint8_t > &Vec, std::vector< uint8_t > &compressedData);


    /*! \brief decompress - dekompresja danych z std::vector< uint8_t > compressedData
     *
     *  Obiekty Vec i compressedData sa przekazywane poprzez referencje
     *  Z vektora danych skompresowanych pobierane sa porcje po 7 bitow
     *  Do pobranych danych dopisywane jest 0 jako najmniej znaczacy bit w bajcie (kompresja stratna)
     *  Wyniki sa przekazywane do cektora Vec
     *
     *  \param [in] compressedData – vektor skompresowanych danych
     *  \param [out] Vec - vektor, w ktorym zostaja zapisane zdekompresowane dane
     *
     *  \warning na wejscie nalezy podawac wektor utworzony za pomoca funkcji compress, inaczej funkcja moze sie wysypac
     */
        void decompress(std::vector< uint8_t > &Vec, std::vector< uint8_t > &compressedData);

};

#endif // SEVENBITCOMP_H

#include "sevenbitcomp.h"
#include <vector>
#include <stdint.h>
#include <qDebug>

SevenBitComp::SevenBitComp()
{
    //ctor
}

SevenBitComp::~SevenBitComp()
{
    //dtor
}


void SevenBitComp::compress(std::vector< uint8_t > &Vec, std::vector< uint8_t > &compressedData)
{
    uint8_t c1, c2;
    uint32_t i;

    int przesuniecie = 1;

    for(i = 0; i < Vec.size(); i++){

        c1 = Vec[i];
        c1 = c1 & 0xFE;                   //dzielenie całkowite przez 2 - kompresja stratna
        c1 = c1 << (przesuniecie-1);     //przesunięcie bitowe (usunięcie pierwszych (i+1)%8 bitów)

        if (i+1 == Vec.size()){     //obsluga ostatniego bajtu

            compressedData.push_back(c1); // do ostatniego bajtu nic nie dopisujemy

        }
        else{           //obsluga normalnego bajtu, ktory nie jest na koncu

            c2 = Vec[i+1];
            c2 = c2 & 0xFE;               //usuwamy najstarszy bit
            c2 = c2 >> (8-przesuniecie); //ustawiamy je na wlasciwej pozycji
            c1 += c2;                    //scalanie

            compressedData.push_back(c1);

            przesuniecie++;
            przesuniecie = przesuniecie%8;
            if(przesuniecie == 0) {                 //doszlismy do momentu gdzie caly nastepny znak zostal dopisany
                przesuniecie ++;
                i ++;
            }
        }
    }
}

void SevenBitComp::decompress(std::vector< uint8_t > &Vec, std::vector< uint8_t > &compressedData)
{

    uint8_t c1, c2, counter;
    int przesuniecie = 0;
    uint32_t i = 0;
    counter = 0;


    while(i < compressedData.size()){


        if((counter == 0)||(counter == 7)){

            if(counter == 0){ // bez najmlodszego bitu

                c1 = compressedData[i];
                c1 = c1 & 0xFE;

                Vec.push_back(c1);
                przesuniecie++;
                counter++;
            }
            else{ // bez najstarszego bitu

                c1 = compressedData[i];
                c1 = c1 << 1;
                Vec.push_back(c1);
                counter = 0;
                przesuniecie = 0;
                i++;
            }

        }
        else{       // pobieramy bity z dwoch bajtow

            c1 = compressedData[i];
            c1 = c1 << (8-przesuniecie);     //interesuje nas tylko n ostatnich bitow z tego bajtu


            if (i+1 == compressedData.size()){        //obsluga ostatniego bajtu

                c1 = c1 & 0xFE;

                Vec.push_back(c1);
                i ++;

            }
            else{           //obsluga normalnego bajtu, ktory nie jest na koncu pliku

                c2 = compressedData[i+1];
                c2 = c2 >> przesuniecie;                //usuwamy najstarszy bit
                c1 += c2;                               //scalanie
                c1 = c1 & 0xFE;

                Vec.push_back(c1);

                przesuniecie++;
                i++;
                counter++;
            }
        }

    }
    if(Vec.size()%3 != 0) Vec.pop_back(); //jesli ostatni bajt byl dopisanymi zerami(?)

}

#ifndef SCALE_H
#define SCALE_H

#include <iostream>

/*  Class for calculating & storing image scale
    Constructor grabs size of the displaying frame
    You can set the size of image by
    -adjust() with parameters x,y
    -setX/Y()

    New adjust() is needed after using setX/Y
    enum mode - determines type of scalling
*/
class Scale
{
    /*! \class Scale scale.h
     *  \brief Klasa obliczajaca skale i pozycje obrazu
     *
     *  Klasa odpowiedzialna za obliczanie i przechowywanie skali obrazu
     *  oraz pozycji na wystwietlanym oknie
     *   \param [in] frame_x – szerokosc okna [pix]
     *   \param [in] frame_y – wysokosc okna [pix]
     *   \param [in] x – szerokosc wyswietlanego obiektu [pix]
     *   \param [in] y – wysokosc wyswietlanego obiektu [pix]
     */
public:
     /*! \brief Konstruktor domyslny
      *
      *
      *
      * Domyslny konstruktor, w ktorym wartosci okna nie zostaly przyisane
      */
    Scale();
    /*! \brief Konstruktor
     *
     *  Jako argumenty przyjmuje 2 zmienny typu unsigned int okreslajace rozmiary okna wyswietlajacego
     *  //! \param [in] frame_x – szerokosc okna [pix]
     *  //! \param [in] frame_y – wysokosc okna [pix] Domyslny konstruktor, w ktorym wartosci okna nie zostaly przypisane
     */
    Scale(unsigned int frame_x,unsigned int frame_y);
    /*! \brief Destruktor
     *
     *  Niszczenie obiektu Scale.
     */

    ~Scale();
    /*! Enum mode - wyliczenia w odpowiednim trybie */
    enum mode
    {
        keep_ratio,             /*!< zachowanie proporcji */
        fit_to_screen,          /*!< dopasowanie do okna */
        stretch_and_keep_ratio, /*!< rozciagniecie z zachowaniem proporcji */
        stretch_to_fit          /*!< rozciagniecie z dopasowaniem do okna */
    };
    /*! \brief adjust - obliczenie skal w osia OX i OY
     *
     *  Jako argumenty przyjmuje 2 zmienny typu unsigned int okreslajace rozmiary okna wyswietlajacego
     *  //! \param [in] x – szerokosc wyswietlanego obiektu [pix]
     *  //! \param [in] y – wysokosc wyswietlanego obiektu [pix]
     *  //! \param [in] center – centrowanie obrazu w oknie
     *      \param [in] arg - tryb skalowania
     */
    void adjust(unsigned int x,unsigned int y,bool center=true,mode arg =keep_ratio);

    /*! \brief adjust - przeladowanie funkcji
     *
     *  //! \param [in] center – centrowanie obrazu w oknie
     *
     *  Funkcja nie przyjmuje parametrow za wyjatkiem center,
     *  Jej zastosowanie ma sens w przypadku skorzystania z publicznych metod setX,setY.
     *  Skaluje z zachowaniem proporcji.
     *
     */
    void adjust(bool center=true);
    /*! \brief getXScale - getter skali X
     *
     *
     * Zwracana wartosc to float z zakresu 0-1
     */
    float getXScale();
    /*! \brief getYScale - getter skali Y
     *
     *
     * Zwracana wartosc to float z zakresu 0-1
     */
    float getYScale();
    /*! \brief setX - setter dla wysokosci obrazu
     *
     *
     * Wymaga wykonania funkcji adjust,w celu aktualizacji wartosci skali
     */
    void setX(unsigned int x);
    /*! \brief setMode - setter dla trybu skalowania
     *
     *
     * Wymaga wykonania funkcji adjust,w celu aktualizacji wartosci skali
     */
    void setMode(mode arg);
    /*! \brief setY - setter dla szerokosci obrazu
     *
     *
     * Wymaga wykonania funkcji adjust,w celu aktualizacji wartosci skali
     */
    void setY(unsigned int y);
    /*! \brief setX - setter dla wysokosci okna
     *
     *
     * Wymaga wykonania funkcji adjust,w celu aktualizacji wartosci skali
     */
    void setframeX(unsigned int x);
    /*! \brief setY - setter dla szerokosci okna
     *
     *
     * Wymaga wykonania funkcji adjust,w celu aktualizacji wartosci skali
     */
    void setframeY(unsigned int y);
    /*! \brief getPosX - getter pozycji X
     *
     *
     * Zwracana wartosc dla gornego lewego rogu.
     * Zwraca 0 w przypadku braku wykonania setPosition()
     */
    unsigned int getPosX();
    /*! \brief getPosY - getter pozycji Y
     *
     *
     * Zwracana wartosc dla gornego lewego rogu
     * Zwraca 0 w przypadku braku wykonania setPosition()
     */
    unsigned int getPosY();


private:

    /*! \privatesection
     *  zbior prywatnych zmiennych  */
    float XScale;       /*!< skala OX */
    float YScale;       /*!< skala OY */
    unsigned int img_x; /*!< szerokosc obrazu */
    unsigned int img_y; /*!< wysokosc obrazu */
    unsigned int win_x; /*!< szerokosc okna */
    unsigned int win_y; /*!< wysokosc okna */

    mode flag_t;        /*!< tryb dopasowania */
    /*! \brief setY - centrowanie obrazu na srodku ekranu
     *
     *
     * wykonynwana automatycznie w trakcie adjust(). Jezeli true to:
     * Ustawia wartosc pos_x i pos_y (gorny lewy rog) tak aby obraz byl wycentrowany
     * W innym przypadku pos_x i pos_y zostaja wyzerowane
     */
    void setPosition(bool center);
    unsigned int pos_x; /*!< pozycja gornego lewego rogu OX */
    unsigned int pos_y; /*!< pozycja gornego lewego rogu OY*/
    /*! \brief calculate - obliczenie skali
     *
     *
     * metoda prywatna majaca na celu wyliczenie skali na podstawie dostarczonych danych.
     * Wywolywanie w przed zdobyciem danych na temat obrazu,ekranu i typu skalowania moze doprowadzic
     * do niepozadanego zachowania
     */
    void calculate(mode arg);


};



#endif // SCALE_H

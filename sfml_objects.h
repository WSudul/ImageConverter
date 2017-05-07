#ifndef SFML_OBJECTS_H
#define SFML_OBJECTS_H

#include <SFML/Graphics.hpp>

class SFML_Objects
{
    /*! \class SFML_Objects sfml_objects.h
     *  \brief Klasa stanowiaca ogolny kontener dla obiektow SFML
     *
     *
     *  Klasa odpowiedzialna za przechowywanie wybranych obiektow SFML
     *  Zaklada sie, ze na potrzeby wyswietlania obrazu na pojedynczym oknie
     *  wystarczy 1 instancja obiektu, ktora bedzie miala zmieniana zawartosc
     *  obiektu Texture oraz Sprite. Obiekt Image zostaje dolaczony jako element
     *  dodatkowy, do ktorego mozliwe byloby zaladowanie obrazu w celu manipulacji
     *  poszczegolnymi pikselami.
     *  Obiekty *Texture, *Sprite, *Image sa w zalozeniu dynamicznie alokowanymi obiektami.
     *  Celem ma byc rekonstrukcja konstruktora z zalozeniem wykorzystania
     *  placement new i pracy z pojedynczym obiektem w wielu watkach.
     *
     *
     */


public:
    /*! \brief Konstruktor domyslny
     *
     * Tworzy wymienione obiekty
     */
    SFML_Objects();
    /*! \brief Destruktor domyslny
     *
     * Niszczy wymienione obiekty
     */
    ~SFML_Objects();
    sf::Texture *Texture; /*!< dynamicznie alokowany obiekt sf::Texture */
    sf::Sprite *Sprite;/*!< dynamicznie alokowany obiekt sf::Sprite */
    sf::Image *Image;/*!< dynamicznie alokowany obiekt sf::Image */




};


#endif // SFML_OBJECTS_H

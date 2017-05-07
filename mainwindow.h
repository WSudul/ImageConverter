#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <ctime>
#include <vector>
#include <QMainWindow>
#include <QString>
#include <QListWidgetItem>
#include <QTWidgets>
#include "sfml_objects.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <iterator>
#include <string>
#include <QDebug>
#include <iostream>
#include <scale.h>
#include <vec_extr.h>
#include <fstream>
#include "SevenBitComp.h"
#include "RLE_c.h"

//! @file
//! Mainwindow - plik naglowkowy

/*! \mainpage Aplikacja
 *
 * \section Wstep
 *
 * Aplikacja konwertujaca bitmapy do formatu utworzonego na potrzeby projektu z GKiM.
 * Opracowana przy uzyciu framework'a QT i biblioteki SFML
 *
 * \section Wymagania
 * \subsection Biblioteki
 *   - QT - wersja 5.7
 *   - SFML - wersja 2.4.1 skompilowana pod uzywany kompilator
 *
 * \subsection Sprzetowe
 *  |       | Minimalne     | Zalecane  |
 *  | :---: | :----:        | :----:    |
 *  | RAM   | 32 MB         | 64 MB     |
 *
 *
 * \section Pliki naglowkowe
 * Pliki naglowkowe nalezace do biblioteki SFML sa dolaczone w nastepujacy sposob:
 *  \code{.cpp}
 *  #include<SFML/example.h>
 *  \endcode
 *
 *  Sposob dolaczenia tych bibliotek pokazuje plik .pro
 *  \snippet test4.pro Linking Headers
 *
 *
 * \section Origins
 * Basic code, on top of which im writing QSFML, was created by "jueves", you can find original post <a href=" http://becomingindiedev.blogspot.com/2013/10/qt-5-and-sfml-20-integration.html">here</a>
 */



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public SFML_Objects
{
    Q_OBJECT


protected:
    /*! \brief nadpisanie zdarzenia wyjscia z okna QMainWindow
     *
     *
     *
     *  Nadpisanie eventu umozliwia wyswietlenie okna z dialogiem
     *  oraz przeprowadzenie zamkniecia pozostalych elementow aplikacji
     */
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

public:
    /*! \brief Konstruktor okna glownego
     *
     *
     *
     *  Konstruktor okna glownego programu, w ktorym zostaly osadzone wszystkie
     *  elementy interfejsu (przyciski, listy, pola tekstowe etc)
     */
    explicit MainWindow(QWidget *parent = 0);
    /*! \brief Destruktor okna glownego
     *
     *
     *
     *  Destruktor okna glownego programu, w ktorym zostaly osadzone wszystkie
     *  elementy interfejsu (przyciski, listy, pola tekstowe etc)
     */
    ~MainWindow();

private slots:
    /*! \brief Slot wywolujacy metody zwiazane z sf::RenderWindow
     *
     *
     *
     * Funkcja przechwytujaca zdarzenie podwojnego klikniecia na wybrany przedmiot z listy
     * Wywoluje ona funkcje odpowiedzialne za utworzenie lub odtworzenie okna wyswietlajacego
     * (sf::RenderWindow Viewer) oraz prywatna metode SFML_display() odpowiedzialna za kontrole
     * nad oknem.
     */
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    /*! \brief Slot ladujacy przedmioty do listy
     *
     *
     * Uruchamia okno dialogu, ktore ma mozliwosc wyboru listy plikow (ladowanych do QStringList)
     * ktore nastepnie sa importowane do obiektu QListWidget.
     * Mozliwy jest wybor filtru na rodzaj importowanych plikow w celu lepszego wyboru zadanych plikow.
     * Obiekt QListWidget (ListWidget) przechowuje nazwe i sciezke do pliku.
     */
    void on_load_pushButton_clicked();

    /*! \brief Slot usuwajacy zaznaczone elementy z obiektu ListWidget
     *
     *  Umozliwia usuniecie wybranych elementow z listy.
     */
    void on_remove_selected_pushButton_clicked();
    /*! \brief Slot odpowiedzialny za konwersje plikow
     *
     *  Przypisany do przycisku convert_pushButton.
     *  Przed wywolaniem oczekiwanej metody konwersji sprawdza, czy dany plik:
     *  -ma odpowiednie rozszerzenie
     *  -da sie zaladowac jako obiekt sf::Image oraz skopiowac zawartosc do wektora
     *
     *  \n Podczas pracy bedzie wyswietlal pasek postepu oraz informowal o aktualnie procesowanym pliku.
     *
     */
    void on_convert_pushButton_clicked();
    /*! \brief Slot odpowiedzialny za rekonwersje plikow
     *
     *  Przypisany do przycisku convert_pushButton.
     *  Przed wywolaniem oczekiwanej metody konwersji sprawdza, czy dany plik:
     *  -ma odpowiednie rozszerzenie
     *
     *  \n Podczas pracy bedzie wyswietlal pasek postepu oraz informowal o aktualnie procesowanym pliku.
     *
     */
    void on_reconvert_pushButton_clicked();

private:

    Ui::MainWindow *ui;
    struct unsigned_pair
    {
        uint32_t x;
        uint32_t y;
    };
    unsigned_pair Viewer_def_size;
    QResource logo; /*!< obiekt przechowujacy logo.png */
    QResource logo_error; /*!< obiekt przechowujacy logo_error.png */

    /*! \brief wyswietlenie zapytania o potwierdzenie wyjscia z aplikacji
     *
     *  Metoda wyswietla okno z zapytaniem i zwraca true, w przypadku potwierdzenia
     *  oraz false dla kazdego inengo przypadku (klikniecie No lub zamkniecie okna)
     */
    bool quit_ask();
    /*! \brief zaladowanie tekstury z pliku do sprite
     *
     *  Jako argumenty przyjmuje 3 zmienne
     *  \param [in] item – obiekt z QListWidget zawierajacy adres do pliku
     *  \param [in] obj – obiekt zawierajacy sf::Texture i sf::Sprite
     *  \param [in] Window - okno na podstawie ktorego dobierana jest skala
     *
     *  Podczas ladowania, automatycznie dobierze skale i pozycje obrazu wzgledem
     *  domyslnych argumentow obiektu typu Scale;
     *  W przypadku niepowodzenia ladowania obrazu metoda (loadfromFile) obraz zastapiony zostanie
     *  obrazem logo_error zaladowanym przez metode SFML_QRes
     *
     */
    bool SFML_load(QListWidgetItem *item,SFML_Objects &obj,sf::RenderWindow &Window);
    /*! \brief wyswietlenie sprite'a na zadanym oknie
     *
     *  Jako argumenty przyjmuje 3 zmienne
     *  \param [in] item – obiekt z QListWidget zawierajacy adres do pliku
     *  \param [in] obj – obiekt zawierajacy sf::Texture i sf::Sprite
     *  \param [in] Window - okno na podstawie ktorego dobierana jest skala
     *
     *  Metoda ma na celu zapewnic obsluge zdarzen podczas przegladania zgromadzonych plikow takich jak:
     *  -zmiana obrazka na nastepny na liscie
     *  -zmiana rozmiaru okna
     *  -zamykanie okna (poprzez przycisk oraz klawisz Esc)
     *
     */
    void SFML_display(QListWidgetItem*item, SFML_Objects &obj,sf::RenderWindow &Window);
    /*! \brief zaladowanie do tekstury i sprite'a obrazu QResource
     *
     *  Jako argumenty przyjmuje 2 zmienne
     *  \param [in] obj – obiekt zawierajacy sf::Texture* i sf::Sprite*
     *  \param [in] res - obiekt zawierajacy odpowiedni obraz
     *
     *  Wykonuje metode loadFromMemory, ktora przypsisuje do obiektu sf::Texture obiekt QResource
     *  Zwraca true w przypadku sukcesu (czyli poprawnego zaladowania tekstury oraz sprite'a).
     *  W przypadku niepowodzenia, tekstura nie ulega zmianie.
     */
    bool SFML_QRes(SFML_Objects &obj,QResource &res);

    void convert(std::vector<uint8_t> vector,std::string name,ImgBaseInfo info,const uint8_t compression);
    void reconvert(std::string name);

    sf::RenderWindow Viewer; /*! obiekt wyswietlajacy okno z obrazami */

    //#pragma pack(push,2)
    struct AAJWHEADER
    {
        uint32_t    FIdentifier;
        unsigned_pair FSize;
        uint32_t    FDataSize;
        uint8_t     FCompression;
    };
    //#pragma pack(pop)
};

#endif // MAINWINDOW_H

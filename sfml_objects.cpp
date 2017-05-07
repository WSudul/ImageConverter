#include "sfml_objects.h"

SFML_Objects::SFML_Objects()
{

    Texture=new sf::Texture;
    Sprite =new sf::Sprite;
    Image= new sf::Image;


}


SFML_Objects::~SFML_Objects()
{

    delete Texture;
    delete Sprite;
    delete Image;
}

#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "funciones.h"
#include "itemCristal.h"
#include "itemCorazon.h"
#include "casa1.h"
#include "enemigo.h"

class Juego{
    protected:
        int puntos = 0;
        ///FONDO
        sf::Texture fondo;
        sf::Sprite spriteFondo;
        ///CONTADOR
        sf::Font font;
        sf::Text text;
        ///SONIDO
        sf::SoundBuffer buffer;
        sf::Sound soundItem;
        sf::SoundBuffer buffer2;
        sf::Sound soundHeart;
    public:
        void Jugar();
};

#endif // JUEGO_H_INCLUDED

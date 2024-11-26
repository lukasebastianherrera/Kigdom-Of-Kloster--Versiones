#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Juego.h"
#include "botones.h"
#include "CajaDeTexto.h"
#include "Puntaje.h"
#include "ArchivoPuntaje.h"
#include <memory>


class Menu{
    protected:
        sf::Sprite spriteFondo;
        sf::Texture fondo;
        sf::Vector2i PosicionMouse;
        sf::Event event;
        sf::Music MenuMusic;
        bool Reproducir, Visibles, Activos, BotonPuntos;
        std::unique_ptr<std::string> NombreEscrito; ///DEFINICION DE PUNTERO INTELIGENTE (RESPONSABLE DE LA MEMORIA)
        ///UNIQUE_PTR ASEGURA QUE SOLO UNO PUEDA TENER EL NOMBRE EN EL MOMENTO DADO
    public:
        Menu();
        void HacerMenu();
        string getNombreEscrito();
};

#endif // MENU_H_INCLUDED

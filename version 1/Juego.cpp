#include "Juego.h"

void Juego::Jugar(){
    ///INICIO DE VENTANA
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kingdom of Kloster");
    window.setFramerateLimit(60);

    font.loadFromFile("fuente.ttf");

    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setCharacterSize(38);
    text.setPosition(10, 10);

    fondo.loadFromFile("fondo/Pixeleado.png");
    spriteFondo.setTexture(fondo);

    buffer.loadFromFile("sonidos/item.wav");
    soundItem.setBuffer(buffer);

    buffer2.loadFromFile("sonidos/heart.wav");
    soundHeart.setBuffer(buffer2);

    ///INSTANCIA DE LOS OBJ DE CLASE
    Personaje Zarac;
    Enemigo Esqueleto("Enemigos/Esqueleto.png", 60, 120);
    Enemigo Rata("Enemigos/rata2.png", 200, 120);
    Cuadrado forma("objetos/derrumbada.png", 153, 75);
    Cuadrado forma2("objetos/casa3.png", 178, 169);
    Cuadrado forma3("objetos/casa4.png", 171, 153);
    Cuadrado forma4("objetos/casa2.png", 80, 150);
    Cuadrado estatua("objetos/solaire.png", 61, 162);

    Cristal item("objetos/Gema1.png");
    Cristal item2("objetos/Gema2.png");
    Cristal item3("objetos/Gema1.png");
    Cristal item4("objetos/Gema2.png");

    Corazon itemC, itemC2;

    ///RESPAWNS PERSONAJE, ENEMIGOS, ESTRUCTURAS
    Zarac.Respawn(900, 50);
    Esqueleto.Respawn(270, 80);
    Rata.Respawn(50, 230);
    forma.Posicion(80, 70);
    forma2.Posicion(550, 20);
    forma3.Posicion(75, 400);
    forma4.Posicion(600, 400);
    estatua.Posicion(380, 190);

    ///RESPAWN CRISTAL
    item.respawn(800, 800);
    item2.respawn(50, 600);
    item3.respawn(1550, 540);
    item4.respawn(1550, 660);

    ///RESPAWN CORAZON
    itemC.respawn(1100, 50);
    itemC2.respawn(800, 1150);

    ///GAMELOOP
    while (window.isOpen()){
        ///ACTUALIZA LOS ESTADOS DONDE TIENE LA INFORMACION DE LOS INPUTS (PERIFERICOS DE ENTRADA)
        sf::Event event;
        while (window.pollEvent(event)){
            ///NOS PERFMITE CERRAR LA VENTANA
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        ///COMANDOS/CMD

        ///ESTABLECEMOS LAS CORDENADAS PARA EL EJE X e Y

        ///UPDATE
        Zarac.Update();
        if(Zarac.esColision(item)){
            puntos++;
            soundItem.play();
            item.hide();
        }
        if(Zarac.esColision(item2)){
            puntos++;
            soundItem.play();
            item2.hide();
        }
        if(Zarac.esColision(item3)){
            puntos++;
            soundItem.play();
            item3.hide();
        }
        if(Zarac.esColision(item4)){
            puntos++;
            soundItem.play();
            item4.hide();
        }

        if(Zarac.esColision(itemC)){
            soundHeart.play();
            itemC.hide();
        }
        if(Zarac.esColision(itemC2)){
            soundHeart.play();
            itemC2.hide();
        }
        if(Zarac.esColision(forma)){
            Zarac.setPosicion(Zarac.getPosicion() - Zarac.getVelocidad());
        }
        if(Zarac.esColision(forma2)){
            Zarac.setPosicion(Zarac.getPosicion() - Zarac.getVelocidad());
        }
        if(Zarac.esColision(forma3)){
            Zarac.setPosicion(Zarac.getPosicion() - Zarac.getVelocidad());
        }
        if(Zarac.esColision(forma4)){
            Zarac.setPosicion(Zarac.getPosicion() - Zarac.getVelocidad());
        }

        text.setString(std::to_string(puntos));

        ///SE BORRA PARA NO SUPERPONER
        window.clear();

        ///DRAW FONDO
        window.draw(spriteFondo);

        ///DRAW PJ
        window.draw(Zarac);
        window.draw(Esqueleto);
        window.draw(Rata);
        window.draw(forma);
        window.draw(forma2);
        window.draw(forma3);
        window.draw(forma4);
        window.draw(estatua);

        ///DRAW CRISTAL
        window.draw(item);
        window.draw(item2);
        window.draw(item3);
        window.draw(item4);

        ///DRAW CORAZON
        window.draw(itemC);
        window.draw(itemC2);
        window.draw(text);


        ///DISPLAY
        window.display();
    }

        ///LIBERACION DEL JUEGO

}

#include "Juego.h"

void Juego::Jugar(){
    ///INICIO DE VENTANA
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kingdom of Kloster");
    window.setFramerateLimit(60);

    puntoSalud = new int(100);

    font.loadFromFile("Pixeleada.ttf");
    fontVida.loadFromFile("Pixeleada.ttf");

    text.setFont(font);
    TextSalud.setFont(fontVida);
    text.setColor(sf::Color::White);
    TextSalud.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    text.setCharacterSize(30);
    text.setPosition(10, 10);

    TextSalud.setCharacterSize(30);
    TextSalud.setPosition(70, 10);

    fondo.loadFromFile("fondo/Pixeleado.png");
    spriteFondo.setTexture(fondo);

    buffer.loadFromFile("sonidos/item.wav");
    soundItem.setBuffer(buffer);

    buffer2.loadFromFile("sonidos/heart.wav");
    soundHeart.setBuffer(buffer2);

    ///INSTANCIA DE LOS OBJ DE CLASE(MAPA)
    Personaje Zarac;
    Enemigo Esqueleto("Enemigos/Esqueleto.png", 60, 120);
    Enemigo Rata("Enemigos/rata2.png", 180, 120);

    Cuadrado formas[] = {
        Cuadrado("objetos/derrumbada.png", 153, 75),
        Cuadrado("objetos/casa3.png", 178, 169),
        Cuadrado("objetos/casa4.png", 171, 153),
        Cuadrado("objetos/casa2.png", 80, 150),
        Cuadrado("objetos/solaire.png", 61, 162)
    };

    Cristal item("objetos/Gema1.png");
    Cristal item2("objetos/Gema2.png");
    Cristal item3("objetos/Gema1.png");
    Cristal item4("objetos/Gema2.png");

    Corazon itemC, itemC2;

    ///INSTANCIA DE LOS OBJ DE CLASE(PELEA)
    Interfaz InterfazAtaques;
    EnPelea Pelea;
    EnPelea PersonajeP;
    EnPelea EnemigoE;
    EnPelea EnemigoR;

    Boton Botones[] = {
        Boton("Pixeleada.ttf", 200, 30, 105, 450, 30, 255, 255, 255, "Ataque 1")
    };

    ///RESPAWNS PERSONAJE, ENEMIGOS, ESTRUCTURAS
    Zarac.Respawn(900, 50);
    Esqueleto.Respawn(270, 80);
    Rata.Respawn(50, 230);

    formas[0].Posicion(80, 70);
    formas[1].Posicion(550, 20);
    formas[2].Posicion(75, 400);
    formas[3].Posicion(600, 400);
    formas[4].Posicion(380, 190);

    ///RESPAWN CRISTAL
    item.respawn(800, 800);
    item2.respawn(50, 600);
    item3.respawn(1550, 540);
    item4.respawn(1550, 660);

    ///RESPAWN CORAZON
    itemC.respawn(1100, 50);
    itemC2.respawn(800, 1150);

    InterfazAtaques.Posicion();
    Botones[0].Posicion(100, 450);

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

        if(Zarac.esColision(itemC) && *puntoSalud<100){
            if(*puntoSalud + 50 > 100){
                *puntoSalud = 100;
            }
            else{
                *puntoSalud += 50;
            }
            soundHeart.play();
            itemC.hide();
        }
        if(Zarac.esColision(itemC2) && *puntoSalud<100){
            if(*puntoSalud + 50 > 100){
                *puntoSalud = 100;
            }
            else{
                *puntoSalud += 50;
            }
            soundHeart.play();
            itemC2.hide();
        }

        if(Zarac.esColision(formas[0])){
            Zarac.setPosicion(Zarac.getPosicion() - Zarac.getVelocidad());
        }
        if(Zarac.esColision(formas[1])){
            Zarac.setPosicion(Zarac.getPosicion() - Zarac.getVelocidad());
        }
        if(Zarac.esColision(formas[2])){
            Zarac.setPosicion(Zarac.getPosicion() - Zarac.getVelocidad());
        }
        if(Zarac.esColision(formas[3])){
            Zarac.setPosicion(Zarac.getPosicion() - Zarac.getVelocidad());
        }

        ///TEST PELEA
        if(Zarac.esColision(Esqueleto)){
            Visibles = false;
            fondo.loadFromFile("fondo/pelea.png");
            PersonajeP.setTextura("Personaje/ZaracFight.png");
            PersonajeP.setTam(150, 160);
            PersonajeP.Posicion(450, 220);

            EnemigoE.setTextura("Enemigos/Esqueleto.png");
            EnemigoE.setTam(80, 160);
            EnemigoE.Posicion(250, 220);

            Gano = Pelea.Pelear(puntoSalud, 50);

            ///MURIO SI/NO
            if(Gano==true){
                //reloj.restart();
                EnemigoMuerto = true;
            }

            ///RESETEA SI EL ENEMIGO MURIO
            if(EnemigoMuerto /*&& reloj.getElapsedTime().asSeconds() >= 3*/){
                Visibles = true;
                EnemigoMuerto = false;
                Gano = false;
                puntos += 5;
                Esqueleto.Respawn(-100, -100);
                fondo.loadFromFile("fondo/Pixeleado.png");
            }
        }

        if(Zarac.esColision(Rata)){
            Esqueleto.Respawn(-100, -100);
            Visibles = false;
            fondo.loadFromFile("fondo/pelea.png");
            PersonajeP.setTextura("Personaje/ZaracFight.png");
            PersonajeP.setTam(150, 160);
            PersonajeP.Posicion(450, 220);

            EnemigoR.setTextura("Enemigos/rata.png");
            EnemigoR.setTam(80, 150);
            EnemigoR.Posicion(250, 230);

            Gano = Pelea.Pelear(puntoSalud, 50);

            ///MURIO SI/NO
            if(Gano==true){
                //reloj.restart();
                EnemigoMuerto = true;
            }

            ///RESETEA SI EL ENEMIGO MURIO
            if(EnemigoMuerto /*&& reloj.getElapsedTime().asSeconds() >= 3*/){
                Visibles = true;
                EnemigoMuerto = false;
                Gano = false;
                puntos += 5;
                Rata.Respawn(-100, -100);
                fondo.loadFromFile("fondo/Pixeleado.png");
            }
        }

        text.setString(std::to_string(puntos));
        TextSalud.setString("Salud: " + std::to_string(*puntoSalud));

        ///SE BORRA PARA NO SUPERPONER
        window.clear();

        ///DRAW FONDO
        window.draw(spriteFondo);

        ///DRAW PJ
        if(Visibles){
            ///DRAW PJ
            window.draw(Zarac);
            window.draw(Esqueleto);
            window.draw(Rata);
            window.draw(formas[0]);
            window.draw(formas[1]);
            window.draw(formas[2]);
            window.draw(formas[3]);
            window.draw(formas[4]);

            ///DRAW CRISTAL
            window.draw(item);
            window.draw(item2);
            window.draw(item3);
            window.draw(item4);

            ///DRAW CORAZON
            window.draw(itemC);
            window.draw(itemC2);
            window.draw(text);
            window.draw(TextSalud);
        }

        else{
            window.draw(PersonajeP);
            window.draw(EnemigoE);
            window.draw(EnemigoR);
            window.draw(Pelea.getTextHP());
            window.draw(Pelea.getTextHPE());
            window.draw(Pelea.getTextoTurno());

            window.draw(InterfazAtaques);
            window.draw(Botones[0]);
        }


        ///DISPLAY
        window.display();
    }
}

Juego::~Juego(){
    delete puntoSalud;
}

#include "Juego.h"

Juego::Juego(){
    /// inicializar variables
    puntoSalud = new int(100);
    puntos = 0;
    EnemigoActivo = 0;
    Visibles = true;
    EnemigoMuerto = false;
    Gano = false;
    SobreBoton1 = false;
    SobreBoton2 = false;
    Peleando = false;
    EnCambio = false;
    PosicionFinal = false;
    PeleaTerminada = false;
    Reproducir = true;
    fondoMensaje= true;
    fondoMensajeFinal = false;

    /// Setear fuente
    font.loadFromFile("Pixeleada.ttf");

    /// setear fuentes
    text.setFont(font);
    TextSalud.setFont(font);
    text.setColor(sf::Color::White);
    TextSalud.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    /// tama�o y posicion del puntaje
    text.setCharacterSize(30);
    text.setPosition(10, 10);

    //tama�o y posicion de la vida
    TextSalud.setCharacterSize(30);
    TextSalud.setPosition(70, 10);

    /// fondo Pueblo
    fondo.loadFromFile("fondo/Pixeleado.png");
    spriteFondo.setTexture(fondo);


    /// Setear buffer y volumenes para items, corazones, musica al estar en el pueblo, pelea, boss final
    buffer.loadFromFile("sonidos/item.wav");
    soundItem.setBuffer(buffer);

    buffer2.loadFromFile("sonidos/heart.wav");
    soundHeart.setBuffer(buffer2);

    MusicaMapa.openFromFile("sonidos/Musica/MapTheme.wav");
    MusicaMapa.setVolume(20.f);

    MusicaPelea.openFromFile("sonidos/Musica/Normal-Fight.wav");
    MusicaPelea.setVolume(20.f);

    MusicaVictoria.openFromFile("sonidos/Musica/VictoryTheme.wav");
    MusicaVictoria.setVolume(20.f);

    MusicaPeleaFinal.openFromFile("sonidos/Musica/FinalBossTheme.wav");
    MusicaPeleaFinal.setVolume(20.f);
}

void Juego::Jugar(){
    ///INICIO DE VENTANA
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kingdom of Kloster");
    window.setFramerateLimit(60);

    /// Suena la musica del mapa en bucle
    MusicaMapa.play();
    MusicaMapa.setLoop(Reproducir);

    ///INSTANCIA DE LOS personajes y enemigos para draw en el mapa (personaje, rata, esqueleto, artorias(jefe))
    Personaje Zarac;
      /// (Enlace para cargar los personajes, altura, ancho)
    Enemigo Esqueleto("Enemigos/Esqueleto.png", 60, 120);
    Enemigo Rata("Enemigos/rata2.png", 180, 120);
    Enemigo Artorias("Enemigos/ArtoriasMap.png", 250, 250);

    /// cuadrado == casa1.h
    Cuadrado formas[] = {
        ///MAPA MAIN
        /// Declarar casas y tama�os (Enlace para cargar las casas, altura, ancho) -> constructor
        Cuadrado("objetos/derrumbada.png", 153, 75), /// casa arriba izquierda
        Cuadrado("objetos/casa3.png", 178, 169), /// casa abajo derecha
        Cuadrado("objetos/casa4.png", 171, 153), /// casa abajo izquierda
        Cuadrado("objetos/casa2.png", 80, 150), /// casa abajo derecha
        Cuadrado("objetos/solaire.png", 61, 162), /// estatua solaire
        ///MAPA FINAL
        Cuadrado("objetos/CasaDestruida.png", 170, 169),
        Cuadrado("objetos/Escombros.png", 200, 100)
    };
    /// intancia objetos en el mapa que dan exp
    Cristal item("objetos/Gema1.png");
    Cristal item2("objetos/Gema2.png");
    Cristal item3("objetos/Gema1.png");
    Cristal item4("objetos/Gema2.png");
    /// intancia objetos corazon en el mapa que recuperan hp
    Corazon itemC, itemC2;

    ///INSTANCIA DE LOS OBJ DE CLASE(PELEA)
    Interfaz InterfazAtaques; /// -> interfaz -> rectangulo que contiene ataque y ataque fuerte
    EnPelea Pelea; /// objeto para llamar a la pelea
      /// personajes que estan en la pelea
    EnPelea PersonajeP; ///zarac
    EnPelea EnemigoE; /// esqueleto
    EnPelea EnemigoR; /// rata
    EnPelea EnemigoFinal; /// artorias

    /// botones para clickear y pegar
    BotonesPelea Boton1;
    Boton1.Posicion(250, 450);
    BotonesPelea Boton2;
    Boton2.Posicion(250, 500);

    ///RESPAWNS PERSONAJE, posicion de objetos en el mapa y enemigos,
    Zarac.Respawn(410, 0);
    Esqueleto.Respawn(270, 80);
    Rata.Respawn(50, 230);
    Artorias.Respawn(400, 100);

    formas[0].Posicion(80, 70);
    formas[1].Posicion(550, 20);
    formas[2].Posicion(75, 400);
    formas[3].Posicion(600, 400);
    formas[4].Posicion(380, 190);
    formas[5].Posicion(80, 10);
    formas[6].Posicion(550, 20);

    ///RESPAWN CRISTAL
    item.respawn(800, 800);
    item2.respawn(50, 600);
    item3.respawn(1550, 540);
    item4.respawn(1550, 660);

    ///RESPAWN CORAZON
    itemC.respawn(1100, 50);
    itemC2.respawn(800, 1150);

    InterfazAtaques.Posicion();

    ///FIN DEFINICION/INSTANCIA DE LOS OBJETOS

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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                        window.close();
                        MusicaVictoria.stop();
                        MusicaMapa.stop();
                        MusicaPelea.stop();
                        Menu objMenu;
                        objMenu.HacerMenu();
        }
        ///UPDATE
        Zarac.Update(Peleando); /// chequea si se movio wasd (Peleando es un bool por si esta en una pelea no se pueda mover)
        if(Zarac.getCambio()){ /// Zarac getCambio chequea si el personaje fue a la derecha del mapa y carga el siguiente mapa
            fondo.loadFromFile("fondo/EscenarioFinal.png");
            EnCambio = true;
            if(PosicionFinal==false){
                Zarac.Respawn(100, 300);
                PosicionFinal = true;
            }
        }
        if(EnCambio==false){ /// Si en cambio es false Pone sonidos y colisiones a los items del primer mapa y sino las del segundo
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

            if(Zarac.esColision(itemC) && *puntoSalud<100){ /// el corazon recupera 50 de vida (no mas de 100)
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
            /// Colisiones con las casas
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

            ///PELEA ESQUELETO
            if(Zarac.esColision(Esqueleto)){ /// Solo si esta en colision con el esqueleto (No te podes mover)
                MusicaMapa.pause(); /// pausa musica mapa
                if (MusicaPelea.getStatus() != sf::Music::Playing){ /// si la musica de la pelea no se reproduce la activa
                    MusicaPelea.play();
                    MusicaPelea.setLoop(Reproducir);
                }
                Visibles = false; ///visibles drawea los objetos del primer mapa
                Peleando = true; /// peleando drawea los personajes y objetos en la pelea
                EnemigoActivo = 1; /// Para ver que enemigo dibujar (1 esqueleto, 2 rata)
                fondo.loadFromFile("fondo/pelea.png"); ///setea el fondo de la pelea

                ///setea la textura del personaje, tama�o y posicion
                PersonajeP.setTextura("Personaje/ZaracFight.png");
                PersonajeP.setTam(150, 160);
                PersonajeP.Posicion(450, 220);

                ///setea la textura del Enemigo tama�o y posicion
                EnemigoE.setTextura("Enemigos/Esqueleto.png");
                EnemigoE.setTam(80, 160);
                EnemigoE.Posicion(250, 220);

                ///Si el mouse se mueve toma la posicion del mouse y si el boton 1(ligero) o 2(Pesado) contiene al mouse SobreBoton se pone en true
                /// Esto es para chequear que boton tocamos si el 1 o el 2
                if(event.type==sf::Event::MouseMoved){
                    PosicionMouse = sf::Mouse::getPosition(window);
                    if(Boton1.getBounds().contains(PosicionMouse.x, PosicionMouse.y)){
                        SobreBoton1 = true;
                    }
                    else if(Boton2.getBounds().contains(PosicionMouse.x, PosicionMouse.y)){
                        SobreBoton2 = true;
                    }
                }
                if(!PeleaTerminada){ /// PeleaTerminada se setea al terminar 1 vez la pelea, si no al estar en colision las peleas son infinitas
                Gano = Pelea.Pelear(puntoSalud, 50, 10, SobreBoton1, SobreBoton2); ///Pelear recibe (Tus puntos de vida, Vida del enemigo, Da�o del enemigo, y si sobreBoton 1 o 2 es true)
                }

                ///MURIO SI/NO
                if(Gano==true){
                    PeleaTerminada = true;
                    EnemigoMuerto = true;
                }
                ///RESETEA SI EL ENEMIGO MURIO
                if(EnemigoMuerto){
                    fondo.loadFromFile("fondo/EnNegro.png"); ///cambia el fondo
                    MusicaPelea.stop(); /// Pausa la musica de la pelea
                    if(MusicaVictoria.getStatus() != sf::Music::Playing){ /// Si la musica de victoria no se reproducia (siempre no) la reproduce
                        MusicaVictoria.play();
                        MusicaVictoria.setLoop(Reproducir);
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                        Visibles = true; /// Vuelven Las casas, enemigos, items al mapa
                        /// Setea los bool a como estaban antes de la pelea para las proximas
                        PeleaTerminada = false;
                        EnemigoMuerto = false;
                        Gano = false;
                        Peleando = false; /// El personaje se puede volver a mover
                        puntos += 5;
                        Esqueleto.Respawn(-100, -100); /// sacamos al esqueleto del mapa
                        ///Pausa la musica de victoria y reproduce la del mapa
                        MusicaVictoria.stop();
                        MusicaMapa.play();
                        fondo.loadFromFile("fondo/Pixeleado.png"); /// vuelve al fondo del pueblo
                    }
                }
                /// Vuelve a como estaban antes de la pelea
                SobreBoton1 = false;
                SobreBoton2 = false;
            }
            ///PELEA RATA
            if(Zarac.esColision(Rata)){
                MusicaMapa.pause();
                if (MusicaPelea.getStatus() != sf::Music::Playing){
                    MusicaPelea.play();
                    MusicaPelea.setLoop(Reproducir);
                }
                Visibles = false;
                Peleando = true;
                EnemigoActivo = 2;
                fondo.loadFromFile("fondo/pelea.png");
                PersonajeP.setTextura("Personaje/ZaracFight.png");
                PersonajeP.setTam(150, 160);
                PersonajeP.Posicion(450, 220);

                EnemigoR.setTextura("Enemigos/rata.png");
                EnemigoR.setTam(250, 160);
                EnemigoR.Posicion(150, 250);

                if(event.type==sf::Event::MouseMoved){
                    PosicionMouse = sf::Mouse::getPosition(window);
                    if(Boton1.getBounds().contains(PosicionMouse.x, PosicionMouse.y)){
                        SobreBoton1 = true;
                    }
                    else if(Boton2.getBounds().contains(PosicionMouse.x, PosicionMouse.y)){
                        SobreBoton2 = true;
                    }
                }
                if(!PeleaTerminada){
                    Gano = Pelea.Pelear(puntoSalud, 50, 10, SobreBoton1, SobreBoton2);
                }

                ///MURIO SI/NO
                if(Gano==true){
                    PeleaTerminada = true;
                    EnemigoMuerto = true;
                }
                ///RESETEA SI EL ENEMIGO MURIO
                if(EnemigoMuerto){
                    fondo.loadFromFile("fondo/EnNegro.png");
                    MusicaPelea.stop();
                    if(MusicaVictoria.getStatus() != sf::Music::Playing){
                        MusicaVictoria.play();
                        MusicaVictoria.setLoop(Reproducir);
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                        Visibles = true;
                        PeleaTerminada = false;
                        EnemigoMuerto = false;
                        Gano = false;
                        Peleando = false;
                        puntos += 5;
                        Rata.Respawn(-200, -200);
                        MusicaVictoria.stop();
                        MusicaMapa.play();
                        fondo.loadFromFile("fondo/Pixeleado.png");
                    }
                }
                SobreBoton1 = false;
                SobreBoton2 = false;
            }
        }
        else{
            ///CASAS MAPA FINAL
            if(Zarac.esColision(formas[5])){
                Zarac.setPosicion(Zarac.getPosicion() - Zarac.getVelocidad());
            }
            if(Zarac.esColision(formas[6])){
                Zarac.setPosicion(Zarac.getPosicion() - Zarac.getVelocidad());
            }
            ///PELEA ARTORIAS
            if(Zarac.esColision(Artorias)){
                MusicaMapa.pause();
                if(MusicaPeleaFinal.getStatus() != sf::Music::Playing && !EnemigoMuerto){
                    MusicaPeleaFinal.play();
                    MusicaPeleaFinal.setLoop(Reproducir);
                }
                Visibles = false;
                Peleando = true;
                EnemigoActivo = 2;
                fondo.loadFromFile("fondo/pelea.png");
                PersonajeP.setTextura("Personaje/ZaracFight.png");
                PersonajeP.setTam(150, 160);
                PersonajeP.Posicion(450, 220);

                EnemigoFinal.setTextura("Enemigos/ArtoriasFight.png");
                EnemigoFinal.setTam(300, 300);
                EnemigoFinal.Posicion(100, 110);

                if(event.type==sf::Event::MouseMoved){
                    PosicionMouse = sf::Mouse::getPosition(window);
                    if(Boton1.getBounds().contains(PosicionMouse.x, PosicionMouse.y)){
                        SobreBoton1 = true;
                    }
                    else if(Boton2.getBounds().contains(PosicionMouse.x, PosicionMouse.y)){
                        SobreBoton2 = true;
                    }
                }
                if(!PeleaTerminada){
                    Gano = Pelea.Pelear(puntoSalud, 100, 15, SobreBoton1, SobreBoton2);
                }
                ///MURIO SI/NO
                if(Gano==true){
                    PeleaTerminada = true;
                    EnemigoMuerto = true;
                }
                ///RESETEA SI EL ENEMIGO MURIO
                if(EnemigoMuerto){
                    if(fondoMensaje){
                        fondo.loadFromFile("fondo/Mensaje.png");
                    }
                    if(MusicaPeleaFinal.getStatus() == sf::Music::Playing){
                        MusicaPeleaFinal.pause();
                    }
                    if(MusicaVictoria.getStatus() != sf::Music::Playing){
                        MusicaVictoria.play();
                        MusicaVictoria.setLoop(Reproducir);
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                        fondoMensaje=false;
                        fondoMensajeFinal = true;
                    }
                    /// Si presionaste enter y fondoMensajeFinal se puso en true cambia al otro fondo
                    if(fondoMensajeFinal){
                        fondo.loadFromFile("fondo/PantallaFinal.png");
                        //Chequea que hallas presionado enter anteriormente que cambio fondoMnesjae a false
                        if(fondoMensaje== false && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        window.close();
                        MusicaVictoria.pause();
                        Menu objMenu;
                        objMenu.HacerMenu();
                       }
                    }
                }
                SobreBoton1 = false;
                SobreBoton2 = false;
            }
        }
        /// Muestra los puntos y la salud
        text.setString(std::to_string(puntos));
        TextSalud.setString("Salud: " + std::to_string(*puntoSalud));

        ///SE BORRA PARA NO SUPERPONER
        window.clear();

        ///DRAW FONDO
        window.draw(spriteFondo); ///pueblo

        ///DRAW PJ ---- Esto solo los dibuja
        if(Zarac.getCambio()==false){ /// Chequea si estamos en el primer mapa
            if(Visibles){ /// Si visibles es true se dibujan los objetos del mapa
                ///DRAW PJ, Enemigos, Casas
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

                ///DRAW TEXTOS puntaje y salud
                window.draw(text);
                window.draw(TextSalud);
            }
            else{ /// Al estar en Pelea pone visibles en false
                if(EnemigoMuerto==false){ /// Si el enemigo no esta muerto dibuja a zarac y enemigo
                    window.draw(PersonajeP);
                    ///VERIFICAMOS EN QUE PELEA ESTAMOS
                    if(EnemigoActivo==1){
                        window.draw(EnemigoE); ///esqueleto
                    }
                    else if(EnemigoActivo==2){
                        window.draw(EnemigoR); /// rata
                    }
                    /// Textos de vida, vidaEnemigo y combatLog
                    window.draw(Pelea.getTextHP());
                    window.draw(Pelea.getTextHPE());
                    window.draw(Pelea.getTextoTurno());
                    window.draw(Pelea.getTextLog());
                    window.draw(Pelea.getTextLogDamage());
                    ///La interfaz de ataque (Cuadrado con "ataque ligero y ataque fuerte")
                    window.draw(InterfazAtaques);
                    /// Dibuja los botones para poder atacar
                    window.draw(Boton1);
                    window.draw(Boton2);
                }
            }
        }
        else{ /// Al estar en el segundo mapa
            if(Visibles){ /// Al estar en el mapa
                window.draw(Zarac); ///personaje
                window.draw(Artorias); /// Artorias jefe final
                window.draw(formas[5]); ///casa
                window.draw(formas[6]); /// casa2
                window.draw(text); ///Textos puntaje
                window.draw(TextSalud); /// Textos de vida
            }
            else{ /// Al estar en colision con el enemigo (pelea)
                if(EnemigoMuerto==false){
                    window.draw(PersonajeP); ///Zarac
                    window.draw(EnemigoFinal); ///Artorias
                    /// Textos de vida, vidaEnemigo y combatLog
                    window.draw(Pelea.getTextHP());
                    window.draw(Pelea.getTextHPE());
                    window.draw(Pelea.getTextoTurno());
                    window.draw(Pelea.getTextLog());
                    window.draw(Pelea.getTextLogDamage());
                    ///La interfaz de ataque (Cuadrado con "ataque ligero y ataque fuerte")
                    window.draw(InterfazAtaques);
                    /// Dibuja los botones para poder atacar
                    window.draw(Boton1);
                    window.draw(Boton2);
                }
            }
        }
        ///DISPLAY
        window.display();
    }
}

Juego::~Juego(){
    delete puntoSalud;
}

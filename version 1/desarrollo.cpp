#include "funciones.h"
#include "casa1.h"

///PERSONAJE MAIN
Personaje::Personaje(){
    ///LE DAMOS UNA TEXTURA AL PERSONAJE
    _texture.loadFromFile("Personaje/Zarac.PNG");

    _sprite.setTexture(_texture);

    ///ESTABLECEMOS LA VELOCIDAD
    _velocidad = {6, 6};

    ///PARA QUE LA TRANSICI�N DEL SALTO AL CAMBIO DE POSICI�N NO SE NOTE
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2, 0);
}

void Personaje::Update(){
    _velocidad = {0, 0};

    ///MOVIMIENTOS CON LOS INPUTS
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        _texture.loadFromFile("Personaje/back.png");
        _velocidad.y = -6;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        _texture.loadFromFile("Personaje/izq-der.png");
        _velocidad.x = -6;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
         _texture.loadFromFile("Personaje/Zarac.png");
        _velocidad.y = 6;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        _texture.loadFromFile("Personaje/izq-der.png");
        _velocidad.x = 6;
    }

    _sprite.move(_velocidad);


    if(_velocidad.x < 0){
        _sprite.setScale(1, 1);
    }

    else if(_velocidad.x > 0){
        _sprite.setScale(-1, 1);
    }

    ///HACEMOS QUE EL PERSONAJE NO SE SALGA DE LA PANTALLA PARA ARRIBA Y PARA LA IZQ
    if(_sprite.getGlobalBounds().left < 0){
        _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
    }
    if(_sprite.getGlobalBounds().top < 0){
        _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
    }

    ///HACEMOS QUE EL PERSONAJE NO SE SALGA DE LA PANTALLA PARA ABAJO Y PARA LA DER
    if(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 800){
        _sprite.setPosition(800 - (_sprite.getGlobalBounds().width - _sprite.getOrigin().x), _sprite.getPosition().y);
    }
    if(_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 600){
        _sprite.setPosition(_sprite.getPosition().x, 600 - _sprite.getGlobalBounds().height);
    }
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(_sprite, states);
}

void Personaje::Respawn(float x, float y) {
    // Calcula las coordenadas x e y de la mitad de la pantalla
    x = x / 2 - _sprite.getGlobalBounds().width / 2;
    y = y / 2 - _sprite.getGlobalBounds().height / 2;

    // Establece la posici�n del sprite en la mitad de la pantalla
    _sprite.setPosition(x, y);
}
sf::FloatRect Personaje::getBounds() const{
    return _sprite.getGlobalBounds();
}
void Personaje::setPosicion(const sf::Vector2f& posicion){
    _sprite.setPosition(posicion);
}
sf::Vector2f Personaje::getPosicion(){
    return _sprite.getPosition();
}
sf::Vector2f Personaje::getVelocidad() const{
    return _velocidad;
}

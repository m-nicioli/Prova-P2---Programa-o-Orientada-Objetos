// Exemplo 06: player.hpp

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

// Definição da classe Player
class Player {
    public:
        // Construtor: carrega a textura e define a posição inicial do player
        Player();

        // Destrutor: descarrega a textura do player
        ~Player();

        // Método para desenhar o player na tela
        void Draw() const;

        // Método para atualizar o player
        void Update(float deltaTime);

        // Método que verifica se o player colidiu com as bordas da tela
        void CheckScreenLimits();

        // Método que retorna a posição do player
        Vector2 getPosition() const;

        // Método que retorna o raio do círculo de colisão do plauer
        float getRadius() const;

        // Método para diminuir a saúde do player quando ele receber algum dano
        void takeDamage(int damage);

        // Método que retorna a saúde do player
        int getHealth() const;
    
    private:
        Texture2D texture; // Textura do player
        Vector2 position;  // Posição do player na tela
        float speed;       // Velocidade de movimentação do player
        float radius;      // Raio do círculo de colisão do player
        int health;        // Saúde do player
};

#endif
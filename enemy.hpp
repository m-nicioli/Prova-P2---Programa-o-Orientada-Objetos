// Exemplo 06: enemy.hpp

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <raylib.h>
#include "player.hpp"

// Definição da classe Enemy
class Enemy {
    public:
        // Construtor: carrega a textura e define a posição inicial do Enemy
        Enemy();

        // Destrutor: descarrega a textura do Enemy
        ~Enemy();

        // Método para desenhar o Enemy na tela
        void Draw() const;

        // Método para atualizar o Enemy
        void Update(float deltaTime);

        // Método para verificar se o inimigo está fora da tela
        bool isOffScreen() const;

        // Método para verificar a colisão do inimigo com o player
        bool checkCollision(const Player& player) const;

        // Método estático, utilizado para obter o total de instâncias do inimigo
        static unsigned int getEnemyCount();
    
    private:
        Texture2D texture; // Textura do Enemy
        Vector2 position;  // Posição do Enemy na tela
        float speed;       // Velocidade de movimentação do Enemy
        float radius;      // Raio do círculo de colisão do Enemy
        bool movingDown;   // Variável para controlar a direção de movimento

        // Atríbuto estático, utilizado para obter o total de instâncias do inimigo
        static unsigned int enemyCount;
};

#endif
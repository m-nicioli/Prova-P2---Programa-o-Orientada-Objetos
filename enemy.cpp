// Exemplo 06: enemy.cpp

#include "enemy.hpp"

// Diretório da aplicação
extern char *appDir;

// Define e inicializa o atributo estático, dentro de um escopo global
// Neste caso, não utilizamos a palavra reserva 'static'
unsigned int Enemy::enemyCount = 0;

// ----------------------------------------------------------------------------

// Método estático, que retorna o total de inimigos que foram instanciados
// Neste caso, não utilizamos a palavra reservada 'static'
unsigned int Enemy::getEnemyCount(){
    return enemyCount;
}

// ----------------------------------------------------------------------------

// Construtor: carrega a textura e define a posição inicial do enemy
Enemy::Enemy(){
    // Incrementa o total de inimigos
    ++enemyCount;

    // Carrega a textura do enemy
    texture = LoadTexture(TextFormat("%s/assets/images/enemy.png", appDir));

    // Posição inicial do enemy
    position.x = GetRandomValue(0, GetScreenWidth() - texture.width);
    position.y = GetRandomValue(- texture.height, - texture.height - 200);

    // Define a velocidade de movimentação do enemy
    speed = GetRandomValue(20, 140) * 1.0f;

    // Define o raio do círculo de colisao do inimigo
    radius = 50.0f;

    // Indica que o inimigo se move para baixo
    movingDown = true;
}

// ----------------------------------------------------------------------------

// Destrutor: descarrega a textura do enemy
Enemy::~Enemy(){
    // Decrementa o total de inimigos
    --enemyCount;

    // Libera os recursos utilizados pela textura do enemy
    UnloadTexture(texture);
}

// ----------------------------------------------------------------------------

// Método para desenhar o enemy na tela
void Enemy::Draw() const{
    // Renderiza a imagem do enemy na posição correta
    DrawTexture(texture, position.x, position.y, RAYWHITE);

    // Renderiza o círculo de colisão do inimigo (para debug)
    /*
    DrawCircle(
        position.x + texture.width / 2.0f + 2.0f,
        position.y + texture.height / 2.0f,
        radius,
        {0, 0, 255, 100}
    );
    */
}

// ----------------------------------------------------------------------------

// Método para atualizar o enemy
void Enemy::Update(float deltaTime){
    // Movimenta o enemy para baixo
    position.y += speed * deltaTime;

    /*
    // Verifica se o inimigo atingiu o limite inferior da tela
    if (position.y > GetScreenHeight()){
        position.x = GetRandomValue(0, GetScreenWidth() - texture.width);
        position.y = GetRandomValue(- texture.height, - texture.height - 200);
    }
    */

    // Verifica a direção e move o inimigo
    if (movingDown){
        // Movimenta para baixo
        position.y += speed * deltaTime;

        // Teste Zigzag
        // position.y += speed * deltaTime;
        // position.x += sin(deltaTime * 0.5f) * speed;
    }
    else{
        // Movimenta para cima
        position.y -= speed * deltaTime;

        // Teste Zigzag
        // position.y -= speed * deltaTime;
        // position.x += sin(deltaTime * 0.5f) * speed;
    }

    // Verifica se o inimigo atingiu o limite inferior da tela
    if (position.y > GetScreenHeight() + texture.height){
        // Muda a direção para cima
        movingDown = false;

        // Gera uma posição horizontal aleatória
        position.x = GetRandomValue(0, GetScreenWidth() - texture.width);

        // Define uma nova movimentação do inimigo
        speed = GetRandomValue(5, 250) * 1.0f;
    }
    // Verifica se o inimigo atingiu o limite superior da tela
    else if (position.y < 0 - texture.height){
        // Muda a direção para baixo
        movingDown = true;

        // Gera uma posição horizontal aleatória
        position.x = GetRandomValue(0, GetScreenWidth() - texture.width);

        // Define uma nova movimentação do inimigo
        speed = GetRandomValue(5, 250) * 1.0f;
    }
}

// ----------------------------------------------------------------------------

// Método para verificar se o inimigo está fora da tela
bool Enemy::isOffScreen() const{
    // Retorna true se o inimigo saiu da tela
    return position.y > GetScreenHeight();
}

// ----------------------------------------------------------------------------

// Método para verificar a colisão do inimigo com o player
bool Enemy::checkCollision(const Player& player) const {
    // Utiliza um círculo para verificar a colisão entre o inimigo e o player
    return CheckCollisionCircles(position, radius, player.getPosition(), player.getRadius());
}
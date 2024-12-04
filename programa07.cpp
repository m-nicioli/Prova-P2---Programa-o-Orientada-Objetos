// Exemplo 07: exemplo07.cpp utilizado na prova

// Considere o exemplo para o Programa07, desenvolvido durante as atividades da aula sobre escopo e relacionamento de classes.
// Nele, além do programa principal (programa07.cpp), criamos uma classe para gerenciar um jogador (player.cpp e player.hpp) e uma 
// classe para gerenciar os inimigos (enemy.cpp e enemy.hpp).

#include <raylib.h>
#include "player.hpp"
#include "enemy.hpp"
#include <vector>
#include <memory>
#include <algorithm>

// VARIÁVEIS GLOBAIS

// Diretório da aplicação
char *appDir = GetApplicationDirectory();

// ------------------------------------------------------------------------
// Classe de Item
// ------------------------------------------------------------------------

class Item {
public:
    Vector2 position;
    Texture2D texture;

    Item(Vector2 pos) {
        position = pos;
        Image image = LoadImage(TextFormat("%s/assets/images/coin.png", appDir));
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    ~Item() {
        UnloadTexture(texture);
    }

    void Draw() const {
        DrawTexture(texture, position.x, position.y, WHITE);
    }

    void Respawn() {
        position = { GetRandomValue(0, GetScreenWidth()), GetRandomValue(0, GetScreenHeight()) };
    }
};

// ------------------------------------------------------------------------
// Função principal
// ------------------------------------------------------------------------

int main() {
    // Define a janela da aplicação
    InitWindow(800, 600, "Programa 07");

    // Inicializa o dispositivo de áudio
    InitAudioDevice();

    // Variável para controlar o tempo de cada frame
    float deltaTime;

    // Framerate
    SetTargetFPS(60);

    // Instanciamento do player
    Player player;

    // Instanciamento do item
    Item item({400, 300}); // Posição inicial do item

    // Pontuação do jogador
    int score = 0;

    // Vetor para armazenar os inimigos como ponteiros exclusivos
    std::vector<std::unique_ptr<Enemy>> enemies;

    // Loop para instanciamento dos inimigos
    for (int i = 0; i < 10; i++)
        enemies.emplace_back(std::make_unique<Enemy>());

    // Carrega a música de fundo
    Music music = LoadMusicStream(TextFormat("%s/assets/music/music.mp3", appDir));

    // Toca a música em loop
    PlayMusicStream(music);

    // Loop principal do jogo
    while (!WindowShouldClose()) {
        // Atualiza o stream da música
        UpdateMusicStream(music);

        // Retorna o tempo em segundos que o último frame levou para ser processado
        deltaTime = GetFrameTime();

        // Atualiza o player
        player.Update(deltaTime);

        // Atualização da posição de todos os inimigos
        for (auto& enemy : enemies)
            enemy->Update(deltaTime);

        // Remove os inimigos que colidiram com o player
        enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(),
                [&](const std::unique_ptr<Enemy>& enemy) {
                    // Se houve colisão com o player
                    if (enemy->checkCollision(player)) {
                        player.takeDamage(10);
                        return true; // Marca o inimigo para remoção
                    }
                    return false; // Mantém o inimigo
                }),
            enemies.end()
        );

        // Verifica colisão entre o player e o item
        if (CheckCollisionCircles(player.getPosition(), player.getRadius(), item.position, 10.0f)) {
            item.Respawn();
            score++;
        }

        // Início da renderização dos objetos do jogo
        BeginDrawing();

        ClearBackground(BLACK); // Define a cor de fundo

        player.Draw(); // Renderiza o player
        item.Draw();   // Renderiza o item

        // Renderiza todos os inimigos
        for (const auto& enemy : enemies)
            enemy->Draw();

        // Renderiza o texto com o total de inimigos
        DrawText(
            TextFormat("Enemies: %d", (int)enemies.size()),
            GetScreenWidth() - 130.0f,
            20.0f,
            22,
            WHITE
        );

        // Renderiza o texto com a saúde do player
        DrawText(
            TextFormat("Health: %d %%", player.getHealth()),
            GetScreenWidth() - 150.0f,
            50.0f,
            22,
            WHITE
        );

        // Renderiza o texto com o score do player
        DrawText(
            TextFormat("Score: %d", score),
            10, 10, 40, WHITE
        );

        EndDrawing(); // Fim da renderização dos objetos do jogo
    }

    // Libera a memória utilizada pela música de fundo
    UnloadMusicStream(music);

    // Fecha o dispositivo de áudio
    CloseAudioDevice();

    // Fecha a janela e limpa recursos do Raylib
    CloseWindow();

    return 0;
}

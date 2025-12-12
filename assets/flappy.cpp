#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <vector>
#include <iostream>
#include <string>

// --- CONFIGURACIÓN GENERAL ---
const int ANCHO_VENTANA = 800; // Ejemplo de tamaño mediano
const int ALTO_VENTANA = 600;  // Ejemplo de tamaño mediano
const float GRAVEDAD = 0.25f;
const float FUERZA_SALTO = -5.0f;
const float VELOCIDAD_TUBERIAS = 3.0f;

// --- CONFIGURACIÓN VISUAL ---
const int ANCHO_FRAME_BIRD = 15;
const int ALTO_FRAME_BIRD = 15;
const float ESCALA_PAJARO = 3.0f;
const float ANCHO_TUBO = 70.0f;
const float ALTO_TAPA = 30.0f;
const float GAME_OVER_DELAY = 3.0f;
const float PAUSE_COUNTDOWN_DURATION = 3.0f;

// --- POSICIÓN DEL TEXTO DE MENÚ ---
// 🚨 AJUSTE AQUÍ: Aumentamos el divisor para bajar el texto (ej. de 10.0f a 5.0f)
const float POS_Y_MSG_INICIO = ALTO_VENTANA / 5.0f; // Ahora un poco más abajo
const float POS_Y_MSG_CENTRO = ALTO_VENTANA / 2.0f;


// -----------------------------------------------------------------------------------
// FUNCIÓN PARA DIBUJAR TUBERÍA (Estilo Mario Bros)
// -----------------------------------------------------------------------------------
void dibujarTuberiaMamalona(sf::RenderWindow& window, float x, float y, float width, float height, bool esTuboDeArriba) {
    sf::Color verdeClaro(85, 255, 85);
    sf::Color verdeMedio(0, 200, 0);
    sf::Color verdeOscuro(0, 150, 0);
    sf::Color bordeNegro(0, 0, 0);
    float grosorBorde = 3.0f;

    // Cuerpo
    sf::RectangleShape cuerpo(sf::Vector2f(width, height));
    cuerpo.setPosition(x, y);
    cuerpo.setFillColor(verdeMedio);
    cuerpo.setOutlineThickness(grosorBorde);
    cuerpo.setOutlineColor(bordeNegro);
    window.draw(cuerpo);

    // Brillo y Sombra del cuerpo
    sf::RectangleShape brilloCuerpo(sf::Vector2f(10, height)); brilloCuerpo.setPosition(x + 10, y); brilloCuerpo.setFillColor(verdeClaro); window.draw(brilloCuerpo);
    sf::RectangleShape sombraCuerpo(sf::Vector2f(5, height)); sombraCuerpo.setPosition(x + width - 10, y); sombraCuerpo.setFillColor(verdeOscuro); window.draw(sombraCuerpo);

    // Tapa
    float anchoTapa = width + 10.0f;
    float xTapa = x - 5.0f;
    float yTapa = esTuboDeArriba ? (y + height - ALTO_TAPA) : y;

    sf::RectangleShape tapa(sf::Vector2f(anchoTapa, ALTO_TAPA));
    tapa.setPosition(xTapa, yTapa);
    tapa.setFillColor(verdeMedio);
    tapa.setOutlineThickness(grosorBorde);
    tapa.setOutlineColor(bordeNegro);
    window.draw(tapa);

    // Brillo Tapa
    sf::RectangleShape brilloTapa(sf::Vector2f(10, ALTO_TAPA)); brilloTapa.setPosition(xTapa + 15, yTapa); brilloTapa.setFillColor(verdeClaro); window.draw(brilloTapa);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA),
        "Flappy Game",
        sf::Style::Default);

    window.setFramerateLimit(60);

    // 0. CARGA DE MÚSICA DE FONDO (sf::Music)
    sf::Music music;
    bool musicLoaded = false;
    if (music.openFromFile("musica_fondo.ogg")) {
        music.setLoop(true);
        music.setVolume(50);
        musicLoaded = true;
    }
    else {
        std::cerr << "Advertencia: No se pudo cargar musica_fondo.ogg" << std::endl;
    }

    // 0.5 🎶 CARGA DE SONIDO DE GAME OVER (sf::Sound) 🎶
    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverSound;
    bool gameOverSoundLoaded = false;
    if (gameOverBuffer.loadFromFile("game_over.wav")) {
        gameOverSound.setBuffer(gameOverBuffer);
        gameOverSoundLoaded = true;
    }
    else {
        std::cerr << "Advertencia: No se pudo cargar game_over.wav" << std::endl;
    }

    // 0.6 🔔 CARGA DE SONIDO DE PUNTO 🔔
    sf::SoundBuffer pointBuffer;
    sf::Sound pointSound;
    bool pointSoundLoaded = false;
    if (pointBuffer.loadFromFile("point_score.wav")) {
        pointSound.setBuffer(pointBuffer);
        pointSoundLoaded = true;
    }
    else {
        std::cerr << "Advertencia: No se pudo cargar point_score.wav" << std::endl;
    }


    // 1. CARGA DE FUENTE
    sf::Font font;
    bool fontLoaded = false;
    if (font.loadFromFile("arial.ttf")) fontLoaded = true;
    else if (font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) fontLoaded = true;

    // 2. CARGA DE TEXTURAS
    sf::Texture birdTexture;
    bool birdLoaded = birdTexture.loadFromFile("Player_Rainbow.png");
    if (birdLoaded) birdTexture.setSmooth(false);

    sf::Texture backgroundTexture;
    bool bgLoaded = backgroundTexture.loadFromFile("background.png");

    // Sprite Fondo
    sf::Sprite backgroundSprite;
    if (bgLoaded) {
        backgroundSprite.setTexture(backgroundTexture);
        float scaleX = (float)ANCHO_VENTANA / backgroundTexture.getSize().x;
        float scaleY = (float)ALTO_VENTANA / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);
    }

    // 3. SETUP JUGADOR
    sf::Sprite birdSprite;
    sf::RectangleShape birdRect(sf::Vector2f(30, 30));

    if (birdLoaded) {
        birdSprite.setTexture(birdTexture);
        birdSprite.setTextureRect(sf::IntRect(0, ALTO_FRAME_BIRD, ANCHO_FRAME_BIRD, ALTO_FRAME_BIRD));
        birdSprite.setScale(ESCALA_PAJARO, ESCALA_PAJARO);
        birdSprite.setOrigin(ANCHO_FRAME_BIRD / 2.0f, ALTO_FRAME_BIRD / 2.0f);
        birdSprite.setPosition(ANCHO_VENTANA / 6, ALTO_VENTANA / 2);
    }
    else {
        birdRect.setPosition(ANCHO_VENTANA / 6, ALTO_VENTANA / 2);
        birdRect.setFillColor(sf::Color::Yellow);
    }

    // 4. TEXTOS 
    sf::Text scoreText;
    sf::Text msgText;

    // 🚨 MENSAJE DE BIENVENIDA MODIFICADO CON ESPACIOS Y GUIONES 🚨
    const std::string WELCOME_MESSAGE =
        "BIENVENIDO A FLAPPY GAME\n\n"
        "------------------------------\n"
        "- Presione ESPACIO para saltar y comenzar\n"
        "- Presione ESC para Pausar\n"
        "- Presione ENTER para continuar la pausa\n"
        "------------------------------";

    if (fontLoaded) {
        // Puntaje
        scoreText.setFont(font);
        scoreText.setString("Score: 0");
        scoreText.setPosition(10, 10);
        scoreText.setOutlineColor(sf::Color::Black);
        scoreText.setOutlineThickness(2);

        // Mensaje Central (Bienvenida / Game Over)
        msgText.setFont(font);
        msgText.setString(WELCOME_MESSAGE);
        msgText.setCharacterSize(28);
        msgText.setFillColor(sf::Color::White);
        msgText.setOutlineColor(sf::Color::Black);
        msgText.setOutlineThickness(3);

        // Centrar el texto
        sf::FloatRect textRect = msgText.getLocalBounds();
        msgText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        msgText.setPosition(ANCHO_VENTANA / 2.0f, POS_Y_MSG_INICIO);
    }

    // Estructura Tubos
    struct Pipe { sf::RectangleShape collisionBox; bool passed; bool isTop; };
    std::vector<Pipe> pipes;

    float birdVelocity = 0;
    int score = 0;
    int spawnTimer = 0;
    bool isGameOver = false;
    bool gameStarted = false;
    sf::Clock animClock;
    int currentFrame = 0;

    // VARIABLES DE CONTROL DE ESTADO Y TEMPORIZADOR
    sf::Clock gameOverClock;
    bool restartReady = false;
    bool isPaused = false;
    bool isCountingDown = false;
    sf::Clock countdownClock;

    // --- INICIO DE MÚSICA ---
    if (musicLoaded) {
        music.play();
    }

    // --- BUCLE PRINCIPAL ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // ----------------------------------------------------
            // 🛑 MANEJO DE PAUSA (ESC) 🛑
            // ----------------------------------------------------
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (gameStarted && !isGameOver && !isCountingDown && !isPaused) {
                    isPaused = true;
                    if (musicLoaded) music.pause();
                }
            }

            // ----------------------------------------------------
            // ⏯️ MANEJO DE DESPAUSAR (ENTER) ⏯️
            // ----------------------------------------------------
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (isPaused) {
                    isPaused = false;
                    isCountingDown = true;
                    countdownClock.restart();
                    if (musicLoaded && music.getStatus() != sf::Music::Playing) music.play();
                }
            }

            // ----------------------------------------------------
            // 🚀 MANEJO DE SALTO / INICIO / REINICIO (SPACE) 🚀
            // ----------------------------------------------------
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (!gameStarted) {
                    // Caso 1: Iniciar juego
                    gameStarted = true;
                    birdVelocity = FUERZA_SALTO;
                    if (musicLoaded) music.play();
                }
                else if (!isGameOver && !isPaused && !isCountingDown) {
                    // Caso 2: Saltar 
                    birdVelocity = FUERZA_SALTO;
                }
                else if (isGameOver && restartReady) {
                    // Caso 3: Reiniciar después de perder
                    isGameOver = false;
                    gameStarted = false;
                    birdVelocity = 0;
                    pipes.clear();
                    score = 0;
                    restartReady = false;

                    if (fontLoaded) {
                        scoreText.setString("Score: 0");
                        msgText.setString(WELCOME_MESSAGE);
                        sf::FloatRect textRect = msgText.getLocalBounds();
                        msgText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                        msgText.setPosition(ANCHO_VENTANA / 2.0f, POS_Y_MSG_INICIO);
                    }

                    if (birdLoaded) { birdSprite.setPosition(ANCHO_VENTANA / 6, ALTO_VENTANA / 2); birdSprite.setRotation(0); }
                    else birdRect.setPosition(ANCHO_VENTANA / 6, ALTO_VENTANA / 2);

                    if (musicLoaded) {
                        music.stop();
                        music.play();
                    }
                }
            }
        }

        // Animación Pájaro
        if (birdLoaded && animClock.getElapsedTime().asSeconds() > 0.15f) {
            currentFrame = (currentFrame + 1) % 4;
            birdSprite.setTextureRect(sf::IntRect(currentFrame * ANCHO_FRAME_BIRD, ALTO_FRAME_BIRD, ANCHO_FRAME_BIRD, ALTO_FRAME_BIRD));
            animClock.restart();
        }

        // ----------------------------------------------------
        // 🏃 LÓGICA PRINCIPAL DEL JUEGO (Solo si no está Pausado ni Contando) 🏃
        // ----------------------------------------------------
        if (gameStarted && !isGameOver && !isPaused && !isCountingDown) {

            birdVelocity += GRAVEDAD;
            if (birdLoaded) { birdSprite.move(0, birdVelocity); birdSprite.setRotation(birdVelocity * 3.0f); }
            else { birdRect.move(0, birdVelocity); }

            spawnTimer++;
            if (spawnTimer >= 100) {
                int height = rand() % (ALTO_VENTANA - 200) + 100;
                Pipe pBottom; pBottom.isTop = false; pBottom.collisionBox.setSize(sf::Vector2f(ANCHO_TUBO, ALTO_VENTANA - height)); pBottom.collisionBox.setPosition(ANCHO_VENTANA, height); pBottom.passed = false; pBottom.collisionBox.setFillColor(sf::Color::Transparent); pipes.push_back(pBottom);
                Pipe pTop; pTop.isTop = true; pTop.collisionBox.setSize(sf::Vector2f(ANCHO_TUBO, height - 150)); pTop.collisionBox.setPosition(ANCHO_VENTANA, 0); pTop.passed = false; pTop.collisionBox.setFillColor(sf::Color::Transparent); pipes.push_back(pTop);
                spawnTimer = 0;
            }

            sf::FloatRect birdBounds = birdLoaded ? birdSprite.getGlobalBounds() : birdRect.getGlobalBounds();
            sf::Vector2f birdPos = birdLoaded ? birdSprite.getPosition() : birdRect.getPosition();

            // COMPROBACIÓN DE COLISIÓN (Tubería)
            for (size_t i = 0; i < pipes.size(); i++) {
                pipes[i].collisionBox.move(-VELOCIDAD_TUBERIAS, 0);
                if (birdBounds.intersects(pipes[i].collisionBox.getGlobalBounds())) {
                    if (!isGameOver) {
                        isGameOver = true;
                        if (gameOverSoundLoaded) gameOverSound.play();
                        gameOverClock.restart();
                        restartReady = false;
                    }
                }
            }

            if (!pipes.empty() && pipes[0].collisionBox.getPosition().x < -ANCHO_TUBO - 20) pipes.erase(pipes.begin());

            // Colisión con límites de la ventana
            if (birdPos.y < 0 || birdPos.y > ALTO_VENTANA) {
                if (!isGameOver) {
                    isGameOver = true;
                    if (gameOverSoundLoaded) gameOverSound.play();
                    gameOverClock.restart();
                    restartReady = false;
                }
            }

            // Lógica de puntaje y SONIDO DE PUNTO
            for (auto& p : pipes) {
                if (!p.passed && p.collisionBox.getPosition().x < birdPos.x && p.collisionBox.getSize().y > 0) {
                    if (p.isTop == false) {
                        score++;
                        p.passed = true;
                        if (fontLoaded) scoreText.setString("Score: " + std::to_string(score));
                        if (pointSoundLoaded) pointSound.play();
                    }
                }
            }
        }

        // 🚨 LÓGICA DE CUENTA REGRESIVA DE PAUSA 🚨
        if (isCountingDown) {
            float elapsed = countdownClock.getElapsedTime().asSeconds();
            if (elapsed >= PAUSE_COUNTDOWN_DURATION) {
                isCountingDown = false;
            }
        }

        // 🚨 LÓGICA DE TEMPORIZADOR DE GAME OVER 🚨
        if (isGameOver && !restartReady) {
            if (gameOverClock.getElapsedTime().asSeconds() >= GAME_OVER_DELAY) {
                restartReady = true;
            }
        }

        // --- CONTROL DE MÚSICA EN GAME OVER Y PAUSA ---
        if ((isGameOver || isPaused) && musicLoaded && music.getStatus() == sf::Music::Playing) {
            music.pause();
        }
        // ------------------------------------


        // --- DIBUJAR ---
        window.clear(sf::Color(135, 206, 235));

        if (bgLoaded) window.draw(backgroundSprite);
        for (auto& p : pipes) {
            sf::Vector2f pos = p.collisionBox.getPosition();
            sf::Vector2f size = p.collisionBox.getSize();
            dibujarTuberiaMamalona(window, pos.x, pos.y, size.x, size.y, p.isTop);
        }
        if (birdLoaded) window.draw(birdSprite); else window.draw(birdRect);

        // 4. Interfaz (Textos)
        if (fontLoaded) {
            if (!gameStarted) {
                window.draw(msgText);
            }
            else if (isPaused) {
                msgText.setString("PAUSA\n\nPresione ENTER\npara continuar");
                sf::FloatRect textRect = msgText.getLocalBounds();
                msgText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                msgText.setPosition(ANCHO_VENTANA / 2.0f, POS_Y_MSG_CENTRO);
                window.draw(msgText);
            }
            else if (isCountingDown) {
                float elapsed = countdownClock.getElapsedTime().asSeconds();
                int timeRemaining = (int)PAUSE_COUNTDOWN_DURATION - (int)elapsed;
                std::string countdownStr;

                if (timeRemaining > 0) {
                    countdownStr = std::to_string(timeRemaining);
                }
                else {
                    countdownStr = "COMIENCE";
                }

                msgText.setCharacterSize(72);
                msgText.setString(countdownStr);

                sf::FloatRect textRect = msgText.getLocalBounds();
                msgText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                msgText.setPosition(ANCHO_VENTANA / 2.0f, POS_Y_MSG_CENTRO);

                window.draw(msgText);
                window.draw(scoreText);

                msgText.setCharacterSize(28);
            }
            else if (isGameOver) {
                std::string gameOverMsg = "PERDISTE\nScore Final: " + std::to_string(score);
                if (restartReady) {
                    gameOverMsg += "\n\nPresione ESPACIO para continuar";
                }

                msgText.setString(gameOverMsg);
                sf::FloatRect textRect = msgText.getLocalBounds();
                msgText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                msgText.setPosition(ANCHO_VENTANA / 2.0f, POS_Y_MSG_CENTRO);

                window.draw(msgText);
            }
            else {
                window.draw(scoreText);
            }
        }

        window.display();
    }
    return 0;
}
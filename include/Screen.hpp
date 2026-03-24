#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


/**
 * @class Screen
 * @brief Klasa odpowiedzialna za tworzenie i obsługę okna aplikacji.
 *
 * Klasa Screen enkapsuluje inicjalizację SDL2, tworzenie okna,
 * renderera oraz obsługę podstawowych zdarzeń. Działa zarówno
 * na Windows, jak i Linux, zapewniając prosty interfejs do
 * wyświetlania grafiki 2D.
 */
class Screen {
public:

    /**
     * @brief Konstruktor tworzący okno i renderer SDL2.
     *
     * @param title  Tytuł okna.
     * @param width  Szerokość okna w pikselach.
     * @param height Wysokość okna w pikselach.
     *
     * Tworzy okno SDL2 oraz renderer. Jeśli inicjalizacja się nie powiedzie,
     * flaga @ref open zostanie ustawiona na false.
     */
    Screen(const std::string& title, int width, int height);

    /**
     * @brief Destruktor zwalniający zasoby SDL2.
     *
     * Niszczy renderer, okno oraz wywołuje SDL_Quit().
     */
    ~Screen();

    /**
     * @brief Sprawdza, czy okno jest nadal otwarte.
     * @return true jeśli okno działa, false jeśli zostało zamknięte.
     */
    bool isOpen() const;

    /**
     * @brief Obsługuje zdarzenia SDL2.
     *
     * Przetwarza kolejkę zdarzeń SDL. Jeśli użytkownik zamknie okno,
     * ustawia flagę @ref open na false.
     */
    void pollEvents();

    /**
     * @brief Czyści ekran ustawionym kolorem.
     *
     * Domyślnie kolor to czarny (0,0,0,255).
     */
    void clear();

    /**
     * @brief Wyświetla zawartość renderera na ekranie.
     */
    void display();

   
    /**
     * @brief Rysuje prostokąt z wypełnieniem i ramką.
     *
     * Funkcja rysuje prostokąt o zadanej pozycji i rozmiarze. Najpierw
     * wypełnia go kolorem tła, a następnie rysuje ramkę o określonej
     * grubości i kolorze. Wszystkie parametry mają wartości domyślne,
     * dzięki czemu można wywołać metodę bez konieczności ich podawania.
     *
     * @param x Pozycja X lewego górnego rogu prostokąta.
     * @param y Pozycja Y lewego górnego rogu prostokąta.
     * @param width Szerokość prostokąta w pikselach.
     * @param height Wysokość prostokąta w pikselach.
     * @param fillColor Kolor wypełnienia (domyślnie czerwony: {255,0,0,255}).
     * @param borderColor Kolor ramki (domyślnie niebieski: {0,0,255,255}).
     * @param borderThickness Grubość ramki w pikselach (domyślnie 2).
     */
    void DrawRectangle(
    int x, int y,
    int width, int height,
    SDL_Color fillColor = {255, 0, 0, 255},
    SDL_Color borderColor = {0, 0, 255, 255},
    int borderThickness = 2
);

/**
 * @brief Rysuje koło z wypełnieniem i obwódką.
 *
 * Funkcja rysuje koło o zadanym środku i promieniu. Najpierw
 * wypełnia je kolorem fillColor, a następnie rysuje obwódkę
 * o grubości borderThickness i kolorze borderColor.
 *
 * @param centerX Pozycja X środka koła.
 * @param centerY Pozycja Y środka koła.
 * @param radius Promień koła w pikselach.
 * @param fillColor Kolor wypełnienia (domyślnie niebieski: {0,0,255,255}).
 * @param borderColor Kolor obwódki (domyślnie żółty: {255,255,0,255}).
 * @param borderThickness Grubość obwódki w pikselach (domyślnie 3).
 */

/**
 * @brief Rysuje koło z wypełnieniem i obwódką (SDL2_gfx).
 *
 * @param x Środek koła - X.
 * @param y Środek koła - Y.
 * @param radius Promień koła.
 * @param fillColor Kolor wypełnienia (domyślnie niebieski).
 * @param borderColor Kolor obwódki (domyślnie żółty).
 * @param borderThickness Grubość obwódki (domyślnie 3 px).
 */
void DrawCircle(
    int x, int y,
    int radius,
    SDL_Color fillColor = {0, 0, 255, 255},
    SDL_Color borderColor = {255, 255, 0, 255},
    int borderThickness = 3
);

/**
 * @brief Rysuje linię o zadanych punktach i kolorze.
 *
 * @param x1 Początek linii - współrzędna X.
 * @param y1 Początek linii - współrzędna Y.
 * @param x2 Koniec linii - współrzędna X.
 * @param y2 Koniec linii - współrzędna Y.
 * @param color Kolor linii (domyślnie biały).
 * @param thickness Grubość linii w pikselach (domyślnie 2).
 */
void DrawLine(
    int x1, int y1,
    int x2, int y2,
    SDL_Color color = {255, 255, 255, 255},
    int thickness = 2
);

/**
 * @brief Rysuje trójkąt z wypełnieniem i obwódką.
 *
 * @param x1 Wierzchołek 1 - X.
 * @param y1 Wierzchołek 1 - Y.
 * @param x2 Wierzchołek 2 - X.
 * @param y2 Wierzchołek 2 - Y.
 * @param x3 Wierzchołek 3 - X.
 * @param y3 Wierzchołek 3 - Y.
 * @param fillColor Kolor wypełnienia (domyślnie zielony).
 * @param borderColor Kolor obwódki (domyślnie czerwony).
 * @param borderThickness Grubość obwódki (domyślnie 2).
 */
void DrawTriangle(
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    SDL_Color fillColor = {0, 255, 0, 255},
    SDL_Color borderColor = {255, 0, 0, 255},
    int borderThickness = 2
);

/**
 * @brief Rysuje elipsę z wypełnieniem i obwódką.
 *
 * @param cx Środek elipsy - X.
 * @param cy Środek elipsy - Y.
 * @param rx Promień poziomy.
 * @param ry Promień pionowy.
 * @param fillColor Kolor wypełnienia (domyślnie jasnoniebieski).
 * @param borderColor Kolor obwódki (domyślnie czarny).
 * @param borderThickness Grubość obwódki (domyślnie 2).
 */
void DrawEllipse(
    int cx, int cy,
    int rx, int ry,
    SDL_Color fillColor = {0, 128, 255, 255},
    SDL_Color borderColor = {0, 0, 0, 255},
    int borderThickness = 2
);

/**
 * @brief Rysuje tekst na ekranie.
 *
 * @param text Treść tekstu.
 * @param x Pozycja X.
 * @param y Pozycja Y.
 * @param color Kolor tekstu (domyślnie biały).
 * @param fontPath Ścieżka do pliku .ttf (domyślnie "arial.ttf").
 * @param fontSize Rozmiar czcionki (domyślnie 24).
 */
void DrawText(
    const std::string& text,
    int x, int y,
    SDL_Color color = {255, 255, 255, 255},
    const std::string& fontPath = "arial.ttf",
    int fontSize = 24
);


private:
    SDL_Window* window;      ///< Wskaźnik na okno SDL2.
    SDL_Renderer* renderer;  ///< Wskaźnik na renderer SDL2.
    bool open;               ///< Flaga informująca, czy okno jest otwarte.
};

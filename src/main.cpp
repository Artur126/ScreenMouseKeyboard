#include "Screen.hpp"

int main(int argc, char *argv[], char *envp[]) {
    Screen screen("SDL2 Window", 800, 600);
    while (screen.isOpen()) {
        screen.pollEvents();
        screen.clear();
        
        // --- PROSTOKĄT ---
        // Czerwony prostokąt 200x200 z niebieską ramką
        screen.DrawRectangle(
            100, 100, 200, 200,
            {255, 0, 0, 255},      // wypełnienie
            {0, 0, 255, 255},      // ramka
            4                      // grubość ramki
        );

        // --- KOŁO ---
        // Niebieskie koło z żółtą obwódką
        screen.DrawCircle(
            300, 300, 100,
            {0, 0, 255, 255},      // wypełnienie
            {255, 255, 0, 255},    // obwódka
            4                      // grubość obwódki
        );

        // --- LINIA ---
        // Biała linia o grubości 3 px
        screen.DrawLine(
            50, 500, 400, 450,
            {255, 255, 255, 255},  // kolor
            3                      // grubość
        );

        // --- TRÓJKĄT ---
        // Zielony trójkąt z czerwoną obwódką
        screen.DrawTriangle(
            500, 100,
            700, 200,
            550, 350,
            {0, 255, 0, 255},      // wypełnienie
            {255, 0, 0, 255},      // obwódka
            3                      // grubość obwódki
        );

        // --- ELIPSA ---
        // Jasnoniebieska elipsa z czarną obwódką
        screen.DrawEllipse(
            600, 400,
            120, 60,
            {0, 128, 255, 255},    // wypełnienie
            {0, 0, 0, 255},        // obwódka
            3                      // grubość obwódki
        );

        //--- TEKST --- Biały tekst w lewym górnym rogu
        screen.DrawText(
            "Hello SDL2!",
            20, 20,
            {255, 255, 255, 255} // kolor tekstu
        );

        screen.DrawKeyMouseInfo();
        //screen.DrawText("TEST", 100, 100, {0,0,0,255});
        screen.display();
    }   
    return 0;  
}

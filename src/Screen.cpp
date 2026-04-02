#include "Screen.hpp"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <sstream>



Screen::Screen(const std::string& title, int width, int height)
    : window(nullptr), renderer(nullptr), open(true), mouseX(0), mouseY(0), lastKey(-1), 
      width(width), height(height), font(nullptr), mouseLeft(false), mouseRight(false), mouseMiddle(false)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL init error: " << SDL_GetError() << "\n";
        open = false;
        return;
    }

      if (TTF_Init() != 0) {
        std::cerr << "TTF init error: " << TTF_GetError() << "\n";
        open = false;
        return;
    }

    font = TTF_OpenFont(FONT_PATH, 20);
    if (!font) {
        std::cerr << "Font load error: " << TTF_GetError() << "\n";
        open = false;
        return;
    }
    //std::cout << "TTF initialized OK\n" << std::endl;


    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window error: " << SDL_GetError() << "\n";
        open = false;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer error: " << SDL_GetError() << "\n";
        open = false;
    }

}

Screen::~Screen() {
    if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

bool Screen::isOpen() const {
    return open;
}

void Screen::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            open = false;
        }

        if (event.type == SDL_KEYDOWN) {
            lastKey = event.key.keysym.sym;
        }

        if (event.type == SDL_MOUSEMOTION) {
            mouseX = event.motion.x;
            mouseY = event.motion.y;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT)   mouseLeft = true;
            if (event.button.button == SDL_BUTTON_RIGHT)  mouseRight = true;
            if (event.button.button == SDL_BUTTON_MIDDLE) mouseMiddle = true;
        }

        if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT)   mouseLeft = false;
            if (event.button.button == SDL_BUTTON_RIGHT)  mouseRight = false;
            if (event.button.button == SDL_BUTTON_MIDDLE) mouseMiddle = false;
        }
}


}

void Screen::clear() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void Screen::display() {
    SDL_RenderPresent(renderer);
}

void Screen::DrawRectangle(
    int x, int y,
    int width, int height,
    SDL_Color fillColor,
    SDL_Color borderColor,
    int borderThickness
) {
    if (!renderer) return;

    // Wypełnienie
    SDL_Rect fillRect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer, &fillRect);

    // Ramka
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);

    SDL_Rect top    = { x, y, width, borderThickness };
    SDL_Rect bottom = { x, y + height - borderThickness, width, borderThickness };
    SDL_Rect left   = { x, y, borderThickness, height };
    SDL_Rect right  = { x + width - borderThickness, y, borderThickness, height };

    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);
}

void Screen::DrawCircle(
    int x, int y,
    int radius,
    SDL_Color fillColor,
    SDL_Color borderColor,
    int borderThickness
) {
    if (!renderer) return;

    // Wypełnienie koła
    filledCircleRGBA(
        renderer,
        x, y,
        radius,
        fillColor.r, fillColor.g, fillColor.b, fillColor.a
    );

    // Obwódka — rysujemy kilka okręgów o zmniejszającym się promieniu
    for (int i = 0; i < borderThickness; i++) {
        circleRGBA(
            renderer,
            x, y,
            radius - i,
            borderColor.r, borderColor.g, borderColor.b, borderColor.a
        );
    }
}


void Screen::DrawLine(
    int x1, int y1,
    int x2, int y2,
    SDL_Color color,
    int thickness
) {
    if (!renderer) return;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Jeśli grubość = 1, używamy natywnej funkcji
    if (thickness <= 1) {
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        return;
    }

    // Grubsza linia = rysowanie wielu równoległych linii
    for (int i = -thickness/2; i <= thickness/2; i++) {
        SDL_RenderDrawLine(renderer, x1 + i, y1, x2 + i, y2);
        SDL_RenderDrawLine(renderer, x1, y1 + i, x2, y2 + i);
    }
}

void Screen::DrawTriangle(
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    SDL_Color fillColor,
    SDL_Color borderColor,
    int borderThickness
) {
    if (!renderer) return;

    // Wypełnienie — metoda scanline
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);

    int minY = std::min({y1, y2, y3});
    int maxY = std::max({y1, y2, y3});

    for (int y = minY; y <= maxY; y++) {
        std::vector<int> nodes;

        auto edge = [&](int xA, int yA, int xB, int yB) {
            if ((yA < y && yB >= y) || (yB < y && yA >= y)) {
                int x = xA + (y - yA) * (xB - xA) / (yB - yA);
                nodes.push_back(x);
            }
        };

        edge(x1, y1, x2, y2);
        edge(x2, y2, x3, y3);
        edge(x3, y3, x1, y1);

        std::sort(nodes.begin(), nodes.end());

        for (size_t i = 0; i + 1 < nodes.size(); i += 2) {
            SDL_RenderDrawLine(renderer, nodes[i], y, nodes[i+1], y);
        }
    }

    // Obwódka
    DrawLine(x1, y1, x2, y2, borderColor, borderThickness);
    DrawLine(x2, y2, x3, y3, borderColor, borderThickness);
    DrawLine(x3, y3, x1, y1, borderColor, borderThickness);
}

void Screen::DrawEllipse(
    int cx, int cy,
    int rx, int ry,
    SDL_Color fillColor,
    SDL_Color borderColor,
    int borderThickness
) {
    if (!renderer) return;

    // Wypełnienie
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);

    for (int y = -ry; y <= ry; y++) {
        int dx = (int)(rx * sqrt(1 - (double)(y*y) / (ry*ry)));
        SDL_RenderDrawLine(renderer, cx - dx, cy + y, cx + dx, cy + y);
    }

    // Obwódka
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);

    for (int t = 0; t < borderThickness; t++) {
        int rrx = rx - t;
        int rry = ry - t;

        int x = 0;
        int y = rry;
        int rx2 = rrx * rrx;
        int ry2 = rry * rry;
        int err = ry2 - (2 * rry - 1) * rx2;

        while (y >= 0) {
            SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            SDL_RenderDrawPoint(renderer, cx - x, cy + y);
            SDL_RenderDrawPoint(renderer, cx - x, cy - y);
            SDL_RenderDrawPoint(renderer, cx + x, cy - y);

            int e2 = 2 * err;
            if (e2 < (2 * x + 1) * ry2) {
                x++;
                err += (2 * x + 1) * ry2;
            }
            if (e2 > -(2 * y - 1) * rx2) {
                y--;
                err -= (2 * y - 1) * rx2;
            }
        }
    }
}

void Screen::DrawText(
    const std::string& text,
    int x, int y,
    SDL_Color color
) {
    if (!renderer || !font) return;

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect rect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}



void Screen::DrawKeyMouseInfo() {
    SDL_Color black = {0, 0, 0, 255};

    char keyChar = static_cast<char>(lastKey);
    std::stringstream ss;
    ss << "Key dec = " << lastKey << " hex = 0x" << std::hex << lastKey << " char = '" << (isprint(keyChar) ? keyChar : '?') << "'";

    DrawText(ss.str(), 10, 10, black);

    std::stringstream ms;
    ms  <<  "Mouse: " + std::to_string(mouseX) + " : " + std::to_string(mouseY)
        << " Mouse Btn: L=" << (mouseLeft ? "1" : "0")
        << " M=" << (mouseMiddle ? "1" : "0")
        << " R=" << (mouseRight ? "1" : "0");


    std::string mouseStr = ms.str();

    int w, h;
    TTF_SizeText(font, mouseStr.c_str(), &w, &h);

    DrawText(mouseStr, width - w - 10, height - h - 10, black);
}





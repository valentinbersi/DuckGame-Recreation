#include "HudManager.h"

#include <algorithm>
#include <string>

#define SET_FINISHED "assets/hud/set.PNG"
#define LOADING_IMAGE "assets/hud/loading.png"

using SDL2pp::NullOpt;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::SDL;
using SDL2pp::Surface;
using SDL2pp::Texture;

HudManager::HudManager(int& windowWidth, int& windowHeight, Renderer& renderer, bool& transition,
                       bool& roundFinished, bool& setFinished, bool& gameFinished):
        windowWidth(windowWidth),
        windowHeight(windowHeight),
        renderer(renderer),
        transition(transition),
        roundFinished(roundFinished),
        setFinished(setFinished),
        gameFinished(gameFinished) {}

void HudManager::check(
        std::list<DuckData>& ducks, std::list<DuckData>& ducksToRender,
        const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping) {
    /*if (gameFinished) {
        //finished game
    } else*/ if (setFinished) {
        finishedSet(ducks, spritesMapping);
        finishedRound(ducksToRender, spritesMapping);
        setFinished = false;
        roundFinished = false;
    } else if (roundFinished) {
        finishedRound(ducksToRender, spritesMapping);
        roundFinished = false;
    }
}

void HudManager::finishedRound(
        std::list<DuckData>& ducksToRender,
        const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping) {
    auto& winner = ducksToRender.front();

    spritesMapping.at(winner.duckID)->drawWin();
    renderer.Present();

    SDL_Delay(1000);

    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    int size = 10;

    int maxSize = std::max(windowWidth, windowHeight);
    int increment = maxSize / 100;

    while (size < maxSize) {
        Rect rect;
        rect.x = centerX - size / 2;
        rect.y = centerY - size / 2;
        rect.w = size;
        rect.h = size;

        SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, 255);
        SDL_RenderFillRect(renderer.Get(), &rect);
        renderer.Present();

        SDL_Delay(10);
        size += increment;
    }

    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.Get());

    Texture& imageTexture = TextureManager::getTexture(LOADING_IMAGE, renderer);

    int imageWidth = imageTexture.GetWidth();
    int imageHeight = imageTexture.GetHeight();
    Rect imageRect;
    imageRect.x = centerX - imageWidth / 2;
    imageRect.y = centerY - imageHeight / 2;
    imageRect.w = imageWidth;
    imageRect.h = imageHeight;

    renderer.Copy(imageTexture, NullOpt, imageRect);

    renderer.Present();
    SDL_Delay(2000);

    transition = true;
}

void HudManager::finishedSet(
        std::list<DuckData>& ducks,
        const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping) {
    Texture& setTexture = TextureManager::getTexture(SET_FINISHED, renderer);

    int newSize = std::min(windowWidth, windowHeight) / 2;

    Rect setRect;
    setRect.x = (windowWidth - newSize) / 2;
    setRect.y = (windowHeight - newSize) / 2;
    setRect.w = newSize;
    setRect.h = newSize;
    renderer.Copy(setTexture, NullOpt, setRect);

    // Recuadro negro
    Rect borderRect;
    borderRect.x = 100;
    borderRect.y = setRect.y + setRect.h + 10;
    borderRect.w = windowWidth - 200;
    borderRect.h = windowHeight / 5 + 20;

    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, 255);
    SDL_RenderFillRect(renderer.Get(), &borderRect);

    // Recuadro gris
    Rect tableRect = borderRect;
    tableRect.x += 2;
    tableRect.y += 2;
    tableRect.w -= 4;
    tableRect.h -= 4;

    SDL_SetRenderDrawColor(renderer.Get(), 50, 50, 50, 255);
    SDL_RenderFillRect(renderer.Get(), &tableRect);

    showPoints(ducks, tableRect, spritesMapping);
    renderer.Present();
    SDL_Delay(5000);
}

std::string duckIDToString(DuckData::Id id) {
    switch (id) {
        case DuckData::Id::White:
            return "White";
        case DuckData::Id::Orange:
            return "Orange";
        case DuckData::Id::Yellow:
            return "Yellow";
        case DuckData::Id::Grey:
            return "Grey";
        default:
            return "Unknown";
    }
}

void HudManager::showPoints(
        std::list<DuckData>& ducks, Rect& tableRect,
        const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping) {
    if (TTF_Init() == -1) {
        std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
        return;
    }

    TTF_Font* font = TTF_OpenFont("assets/fonts/font.ttf", 24);
    if (!font) {
        std::cerr << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};
    int xOffset = 10;  // Space between ducks

    for (const auto& duck: ducks) {
        std::string scoreText = /*std::to_string(duck.score)*/ "20";
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
        if (!textSurface) {
            std::cerr << "Error al crear la superficie del texto: " << TTF_GetError() << std::endl;
            continue;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer.Get(), textSurface);
        if (!textTexture) {
            std::cerr << "Error al crear la textura del texto: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(textSurface);
            continue;
        }

        // Ducks
        Rect spriteRect;
        spriteRect.x = tableRect.x + xOffset + 40;
        spriteRect.y = tableRect.y + tableRect.h / 2;
        spriteRect.w = 50;
        spriteRect.h = 50;

        // Text
        Rect textRect;
        textRect.x = spriteRect.x - spriteRect.h / 2;
        textRect.y = tableRect.y;
        textRect.w = spriteRect.w;
        textRect.h = spriteRect.w;

        SDL_RenderCopy(renderer.Get(), textTexture, nullptr, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        spritesMapping.at(duck.duckID)->updatePosition(spriteRect.x, spriteRect.y);
        spritesMapping.at(duck.duckID)->setScale(windowHeight / 14.0);
        DuckState& state = spritesMapping.at(duck.duckID)->getState();
        spritesMapping.at(duck.duckID)->update(state);

        xOffset += spriteRect.w + windowWidth / 6;
    }

    TTF_CloseFont(font);
    TTF_Quit();
}

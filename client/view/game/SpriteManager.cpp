#include "SpriteManager.h"

#define DEFAULT_SCALE 2.5f
#define DEFAULT_OFFSET_Y 200

#define SPRITE_IDLE 0
#define FEATHERS_IDLE1_ROW 0
#define FEATHERS_IDLE2_ROW 1

#define SPRITESHEET_JUMP_ROW 1
#define SPRITESHEET_CROUCH_ROW 1
#define SPRITESHEET_CROUCH_COL 5
#define SPRITESHEET_RIGHT_LEFT_ROW 0
#define SPRITESHEET_DEAD_ROW 2
#define SPRITESHEET_PLAYING_DEAD_COL 0
#define SPRITESHEET_DEAD_COL 1

#define NO_FEATHER false
#define NO_RIGHT_FEATHER false
#define FEATHER true
#define RIGHT_FEATHER true

#define OFFSET_RIGHT 3
#define OFFSET_LEFT 3
#define OFFSET_Y 4

SpriteManager::SpriteManager(
        const char* path1, const char* path2,
        SDL2pp::Renderer& renderer /*, int& window_width, int& window_height*/):
        path1(path1),
        path2(path2),
        scale(DEFAULT_SCALE),
        moving_right(false),
        moving_left(false),
        in_air(false),
        flapping(false),
        flip(false),
        spritesheet(std::make_unique<Spritesheet>(path1, path2, renderer)),
        frame(0),
        flappingFrame(0),
        m_position_x(0),
        m_position_y(0) {}

void SpriteManager::updatePosition(float new_x, float new_y) {
    m_position_x = new_x;
    m_position_y = new_y;
}

void SpriteManager::update(bool playing_dead, bool crouching, bool air, bool flap,
                           bool being_damaged, bool right, bool left) {
    if (left)
        flip = true;
    else if (right)
        flip = false;

    if (being_damaged || playing_dead ||
        crouching) {  // no animation; only one sprite for each 'event'
        if (being_damaged) {
            draw(SPRITESHEET_DEAD_COL, SPRITESHEET_DEAD_ROW);
            // do something...? how the game is gonna change for this duck and the others?

        } else if (playing_dead) {
            draw(SPRITESHEET_PLAYING_DEAD_COL, SPRITESHEET_DEAD_ROW);
        } else {
            draw(SPRITESHEET_CROUCH_COL, SPRITESHEET_CROUCH_ROW);
        }
        return;
    }

    setFlags(air, flap, right, left);  // sets flags for animations only
    if (air) {
        draw(frame, SPRITESHEET_JUMP_ROW);

    } else {
        draw(frame, SPRITESHEET_RIGHT_LEFT_ROW);
    }
}

void SpriteManager::draw(int col, int row) {
    // Sprite
    spritesheet->selectSprite(col, row, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER);
    spritesheet->drawSelectedSprite(position, flip, NO_FEATHER/*, NO_RIGHT_FEATHER*/);

    if (not flip) {
        spritesheet->selectSprite(col, row, FEATHER);
        position = getPosition(FEATHER, NO_RIGHT_FEATHER);
        spritesheet->drawSelectedSprite(position, flip, FEATHER/*, NO_RIGHT_FEATHER*/);

    } else if (flip || in_air || flapping /* etc*/) {
        spritesheet->selectSprite(col, row, FEATHER);
        position = getPosition(FEATHER, RIGHT_FEATHER);
        spritesheet->drawSelectedSprite(position, flip, FEATHER/*, RIGHT_FEATHER*/);
    }
}

void SpriteManager::setFlags(bool air, bool flap, bool right, bool left) {
    if (in_air || moving_right || moving_left) {
        if (!(in_air && frame == 4))
            frame++;
        if (frame > 5 && !in_air)
            frame = 0;
    }
    if (flapping) {
        flappingFrame++;
        // if (flappingFrame)
    }

    if (in_air != air) {
        in_air = !in_air;
        frame = 0;
    }
    if (moving_right != right) {
        moving_right = !moving_right;
        frame = 0;
    }
    if (moving_left != left) {
        moving_left = !moving_left;
        frame = 0;
    }
    if (flapping != flap) {
        flapping = !flapping;
        frame = 0;
        flappingFrame = 0;
    }
}

/*void SpriteManager::negateFlag(bool flag, bool& flagToNegate) {
    if (flagToNegate != flag) {
        flagToNegate = !flagToNegate;
        frame = 0;
    }
}*/

SDL2pp::Rect SpriteManager::getPosition(bool isFeather, bool isRightFeather) {
    int spriteWidth = spritesheet->getClipWidth();
    int spriteHeight = spritesheet->getClipHeight();
    // Crear el rectángulo de posición, manteniendo las coordenadas globales (m_position_x, m_position_y)
    SDL2pp::Rect position(m_position_x, m_position_y, spriteWidth * scale, spriteHeight * scale);
    // Si es un sprite de pluma, ajustamos su posición
    if (isFeather) {
        if (isRightFeather) {
            position.x += (spriteWidth * 2 - OFFSET_RIGHT) * scale / DEFAULT_SCALE;
        } else {
            position.x += (spriteWidth / 2 + OFFSET_LEFT) * scale / DEFAULT_SCALE;
        }
        position.y += (spriteWidth * 2 + OFFSET_Y) * scale / DEFAULT_SCALE;  // Ajuste para las plumas
    }

    return position;
}

Spritesheet& SpriteManager::getSpritesheet() {return *spritesheet;}

void SpriteManager::setScale(float newScale) {
    scale = newScale;
}

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

SpriteManager::SpriteManager(const char* path1, const char* path2, SDL2pp::Renderer& renderer,
                             SDL2pp::Texture& m_texture_image, SDL2pp::Texture& m_texture_feathers,
                             int& window_width, int& window_height):
        path1(path1),
        path2(path2),
        scale(DEFAULT_SCALE),
        moving_right(false),
        moving_left(false),
        in_air(false),
        flapping(false),
        flip(false),
        spritesheet(path1, path2, renderer, m_texture_image, m_texture_feathers),
        frame(0),
        flappingFrame(0),
        m_position_x(0),
        m_position_y(0) {

    // Really needed? Idk
    spritesheet.selectSprite(SPRITE_IDLE, SPRITE_IDLE, NO_FEATHER);
    int playerWidth = spritesheet.getClipWidth();
    int playerHeight = spritesheet.getClipHeight();
    m_position_x = (window_width - playerWidth * scale) / 2;
    m_position_y = (window_height - playerHeight * scale) / 2 + DEFAULT_OFFSET_Y;
}

void SpriteManager::updatePosition(float new_x, float new_y) {
    m_position_x = new_x;
    m_position_y = new_y;
}

// un bool 'started' para inicializar el playerWidth etc?
void SpriteManager::update(bool playing_dead, bool crouching, bool air, bool flap,
                           bool being_damaged, bool right, bool left) {
    if (being_damaged || playing_dead ||
        crouching) {  // no animation; only one sprite for each 'event'
        if (being_damaged) {
            draw(SPRITESHEET_DEAD_COL, SPRITESHEET_DEAD_ROW);
            // do something...? how the game is gonna change for this duck and the others?

        } else if (playing_dead) {
            draw(SPRITESHEET_PLAYING_DEAD_COL, SPRITESHEET_DEAD_ROW);
            // draw

        } else {
            draw(SPRITESHEET_CROUCH_COL, SPRITESHEET_CROUCH_ROW);
            // draw
        }
        return;
    }

    setFlags(air, flap, right, left);  // sets flags for animations only
    flip = left;
    if (air) {
        draw(frame, SPRITESHEET_JUMP_ROW);

    } else {
        draw(frame, SPRITESHEET_RIGHT_LEFT_ROW);
    }
}

void SpriteManager::draw(int col, int row) {
    // Sprite
    spritesheet.selectSprite(col, row, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER);
    spritesheet.drawSelectedSprite(position, flip, NO_FEATHER, NO_RIGHT_FEATHER);

    // Left feather
    spritesheet.selectSprite(col, row, NO_FEATHER);
    position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER);
    spritesheet.drawSelectedSprite(position, flip, NO_FEATHER, NO_RIGHT_FEATHER);

    // Right feather
    position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER);
    spritesheet.drawSelectedSprite(position, flip, NO_FEATHER, NO_RIGHT_FEATHER);
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

void SpriteManager::start() {
    spritesheet.selectSprite(SPRITE_IDLE, SPRITE_IDLE, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER);
    spritesheet.drawSelectedSprite(position, flip, NO_FEATHER, NO_RIGHT_FEATHER);

    spritesheet.selectSprite(FEATHERS_IDLE1_ROW, FEATHERS_IDLE1_ROW, NO_FEATHER);
    SDL2pp::Rect feathersPosition = getPosition(NO_FEATHER, NO_RIGHT_FEATHER);
    spritesheet.drawSelectedSprite(feathersPosition, flip, NO_FEATHER, NO_RIGHT_FEATHER);

    spritesheet.selectSprite(FEATHERS_IDLE1_ROW, FEATHERS_IDLE2_ROW, NO_FEATHER);
    SDL2pp::Rect leftFeatherPosition = getPosition(NO_FEATHER, NO_RIGHT_FEATHER);
    spritesheet.drawSelectedSprite(leftFeatherPosition, flip, NO_FEATHER, NO_RIGHT_FEATHER);
}

SDL2pp::Rect SpriteManager::getPosition(bool isFeather, bool isRightFeather) {
    int playerWidth = spritesheet.getClipWidth();
    int playerHeight = spritesheet.getClipHeight();
    SDL2pp::Rect position(m_position_x, m_position_y, playerWidth * scale, playerHeight * scale);

    if (isFeather) {
        // Adjust the position for feathers
        if (isRightFeather) {
            position.x += playerWidth;  // Example adjustment for right feather
        } else {
            position.x -= playerWidth;  // Example adjustment for left feather
        }
        position.y -= 10;  // Example adjustment for feathers, change as needed
    }

    return position;
}

void SpriteManager::incFrame() {
    frame += 1;
    // if frame... ? (caminar y saltar tienen el mismo número de sprites)
    //  pero si empieza a usar las feathers, se quedará en el sprite n = 3 (4)
}

void SpriteManager::incFlappingFrame() { flappingFrame += 1; }

void SpriteManager::resetFrame() { frame = 0; }

void SpriteManager::resetFlappingFrame() { flappingFrame = 0; }

void SpriteManager::changeFlapping() { flapping = !flapping; }

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
#define NO_CHESTPLATE false
#define NO_HELMET false
#define FEATHER true
#define RIGHT_FEATHER true
#define CHESTPLATE true
#define HELMET true

#define OFFSET_RIGHT 3
#define OFFSET_LEFT 3
#define OFFSET_Y 4

SpriteManager::SpriteManager(
        const char* path1, const char* path2,
        SDL2pp::Renderer& renderer, TextureManager& textureManager /*, int& window_width, int& window_height*/):
        path1(path1),
        path2(path2),
        scale(DEFAULT_SCALE),
        moving_right(false),
        moving_left(false),
        in_air(false),
        flapping(false),
        flip(false),
        hasHelmet(true),
        hasChestplate(true),
        spritesheet(std::make_unique<Spritesheet>(path1, path2, renderer, textureManager)),
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
    if (left) flip = true;
    else if (right) flip = false;

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

    negateFlag(air, in_air);
    negateFlag(right, moving_right);
    negateFlag(left, moving_left);

    if (flapping != flap) {
        flapping = !flapping;
        frame = 0;
        flappingFrame = 0;
    }
}

/*void SpriteManager::draw(int col, int row) {
    // Sprite
    spritesheet->selectSprite(col, row, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE);
    spritesheet->drawSelectedSprite(position, flip, NO_FEATHER, NO_RIGHT_FEATHER);

    if (not flip) {
        spritesheet->selectSprite(col, row, FEATHER);
        position = getPosition(FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE);
        spritesheet->drawSelectedSprite(position, flip, FEATHER, NO_RIGHT_FEATHER);

    } else if (flip || in_air || flapping ) {
        spritesheet->selectSprite(col, row, FEATHER);
        position = getPosition(FEATHER, RIGHT_FEATHER, NO_CHESTPLATE);
        spritesheet->drawSelectedSprite(position, flip, FEATHER, RIGHT_FEATHER);
    }

    if (hasChestplate) {
        spritesheet->selectSprite(col, row, NO_FEATHER);
        position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, CHESTPLATE);
        spritesheet->drawChestplate(position, flip);
    }

    if (hasHelmet) {
        spritesheet->selectSprite(2, 0, NO_FEATHER);
        position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE);
        spritesheet->drawHelmet(position, flip);
    }
}*/

void SpriteManager::draw(int col, int row) {
    drawMainSprite(col, row);
    drawFeathers(col, row);
    if (hasChestplate) drawChestplate(col, row);
    if (hasHelmet) drawHelmet();
}

void SpriteManager::drawMainSprite(int col, int row) {
    spritesheet->selectSprite(col, row, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE, NO_HELMET);
    spritesheet->drawSelectedSprite(position, flip, NO_FEATHER);
}

void SpriteManager::drawFeathers(int col, int row) {
    if (!flip) {
        spritesheet->selectSprite(col, row, FEATHER);
        SDL2pp::Rect position = getPosition(FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE, NO_HELMET);
        spritesheet->drawSelectedSprite(position, flip, FEATHER);

    } else if (flip || in_air || flapping) {
        spritesheet->selectSprite(col, row, FEATHER);
        SDL2pp::Rect position = getPosition(FEATHER, RIGHT_FEATHER, NO_CHESTPLATE, NO_HELMET);
        spritesheet->drawSelectedSprite(position, flip, FEATHER);
    }
}

void SpriteManager::drawChestplate(int col, int row) {
    spritesheet->selectSprite(col, row, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, CHESTPLATE, NO_HELMET);
    spritesheet->drawChestplate(position, flip);
}

void SpriteManager::drawHelmet() {
    spritesheet->selectSprite(2, 0, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE, HELMET);
    spritesheet->drawHelmet(position, flip);
}

void SpriteManager::negateFlag(bool flag, bool& flagToNegate) {
    if (flagToNegate != flag) {
        flagToNegate = !flagToNegate;
        frame = 0;
    }
}

SDL2pp::Rect SpriteManager::getPosition(bool isFeather, bool isRightFeather, bool isChestplate, bool isHelmet) {
    SDL2pp::Rect position = calculateBasePosition();
    int spriteHeight = spritesheet->getClipHeight();

    if (isFeather) adjustForFeathers(position, isRightFeather);
    if (isChestplate) if (frame == 0) position.y += (spriteHeight / 2) * scale / DEFAULT_SCALE;
    if (isHelmet) adjustForHelmet(position);

    return position;
}

SDL2pp::Rect SpriteManager::calculateBasePosition() {
    int spriteWidth = spritesheet->getClipWidth();
    int spriteHeight = spritesheet->getClipHeight();
    return SDL2pp::Rect(m_position_x, m_position_y, spriteWidth * scale, spriteHeight * scale);
}

void SpriteManager::adjustForFeathers(SDL2pp::Rect& position, bool isRightFeather) {
    int spriteWidth = spritesheet->getClipWidth();
    int spriteHeight = spritesheet->getClipHeight();

    if (isRightFeather) {
        position.x += (spriteWidth * 2 - OFFSET_RIGHT) * scale / DEFAULT_SCALE;
    } else {
        position.x += (spriteWidth / 2 + OFFSET_LEFT) * scale / DEFAULT_SCALE;
    }
    position.y += (spriteHeight * 2 + OFFSET_Y) * scale / DEFAULT_SCALE;
}

void SpriteManager::adjustForHelmet(SDL2pp::Rect& position) {
    if (flip) position.x -= /*frame*/ 2 * scale / DEFAULT_SCALE;
    else position.x += /*frame*/ 2 * scale / DEFAULT_SCALE;

    position.y -= 14 * scale / DEFAULT_SCALE;
}

Spritesheet& SpriteManager::getSpritesheet() {return *spritesheet;}

void SpriteManager::setScale(float newScale) {
    scale = newScale;
}

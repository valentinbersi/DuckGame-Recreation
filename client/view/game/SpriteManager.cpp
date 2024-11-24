#include "SpriteManager.h"

#include <fstream>

#define DEFAULT_SCALE 2.5f

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
#define NO_WEAPON false
#define NO_EFFECTS false
#define FEATHER true
#define RIGHT_FEATHER true
#define CHESTPLATE true
#define HELMET true
#define WEAPON true
#define EFFECTS true

#define LIMIT_FRAMES 5

#define ROW_WEAPON 3
#define COL_WEAPON 0

SpriteManager::SpriteManager(
        const char* path1, const char* path2,
        SDL2pp::Renderer& renderer /*, int& window_width, int& window_height*/):
        path1(path1),
        path2(path2),
        scale(DEFAULT_SCALE),
        movingRight(false),
        movingLeft(false),
        inAir(false),
        crouching(false),
        flapping(false),
        flip(false),
        hasHelmet(false),
        hasChestplate(false),
        shooting(false),
        gunEquipped(ItemID::CowboyPistol),
        spritesheet(std::make_unique<Spritesheet>(path1, path2, renderer)),
        weaponSpriteManager(std::make_unique<WeaponSpriteManager>()),
        frame(0),
        flappingFrame(0),
        m_position_x(0),
        m_position_y(0) {}

void SpriteManager::updatePosition(float new_x, float new_y) {
    m_position_x = new_x;
    m_position_y = new_y;
}

void SpriteManager::update(const DuckState& state) {
    if (state.moving and state.direction == DuckData::Direction::Left)
        flip = true;
    else if (state.moving and state.direction == DuckData::Direction::Right)
        flip = false;
    setFlags(state);

    if (state.inAir) {
        draw(frame, SPRITESHEET_JUMP_ROW, state);

    } else if (state.beingDamaged || state.playingDead || state.crouching) {
        if (state.beingDamaged) {
            draw(SPRITESHEET_DEAD_COL, SPRITESHEET_DEAD_ROW, state);
            // do something...? how the game is gonna change for this duck and the others?

        } else if (state.playingDead) {
            draw(SPRITESHEET_PLAYING_DEAD_COL, SPRITESHEET_DEAD_ROW, state);
        } else {
            draw(SPRITESHEET_CROUCH_COL, SPRITESHEET_CROUCH_ROW, state);
        }

    } else {
        draw(frame, SPRITESHEET_RIGHT_LEFT_ROW, state);
    }
}

void SpriteManager::updateEquipment(bool helmet, bool chestplate, ItemID& gun) {
    hasHelmet = helmet;
    hasChestplate = chestplate;
    gunEquipped = gun;
}

void SpriteManager::setFlags(const DuckState& state) {
    if (inAir || movingRight || movingLeft) {
        if (!(inAir && frame == 4))
            ++frame;
        if (frame > LIMIT_FRAMES && !inAir)
            frame = 0;
    }
    if (flapping) {
        ++flappingFrame;
    }

    negateFlag(state.inAir, inAir);
    negateFlag(state.movingRight, movingRight);
    negateFlag(state.movingLeft, movingLeft);
    negateFlag(state.crouching, crouching);
    negateFlag(state.isShooting, shooting);

    if (flapping != state.flapping) {
        flapping = !flapping;
        frame = 0;
        flappingFrame = 0;
    }
}

void SpriteManager::negateFlag(bool flag, bool& flagToNegate) {
    if (flagToNegate != flag) {
        flagToNegate = !flagToNegate;
        frame = 0;
    }
}

void SpriteManager::draw(int col, int row, const DuckState& state) {
    drawMainSprite(col, row);
    bool hasWeapon = false;

    if (hasChestplate)
        drawChestplate(col, row);
    if (hasHelmet)
        drawHelmet();
    if (gunEquipped != ItemID::NONE) {
        SDL2pp::Rect position = calculateBasePosition();
        weaponSpriteManager->drawWeapon(spritesheet.get(), position, flip, scale, state);
        hasWeapon = true;
    }
    drawFeathers(col, row, hasWeapon);
}

void SpriteManager::drawMainSprite(int col, int row) {
    spritesheet->selectSprite(col, row, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE, NO_HELMET);
    spritesheet->drawSelectedSprite(position, flip, NO_FEATHER);
}

void SpriteManager::drawFeathers(int col, int row, bool hasWeapon) {
    if (!flip) {
        if (hasWeapon)
            spritesheet->selectSprite(COL_WEAPON, ROW_WEAPON, FEATHER);
        else
            spritesheet->selectSprite(col, row, FEATHER);
        SDL2pp::Rect position = getPosition(FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE, NO_HELMET);
        spritesheet->drawSelectedSprite(position, flip, FEATHER);

    } else if (flip || inAir || flapping) {
        if (hasWeapon)
            spritesheet->selectSprite(COL_WEAPON, ROW_WEAPON, FEATHER);
        else
            spritesheet->selectSprite(col, row, FEATHER);
        SDL2pp::Rect position = getPosition(FEATHER, RIGHT_FEATHER, NO_CHESTPLATE, NO_HELMET);
        spritesheet->drawSelectedSprite(position, flip, FEATHER);
    }
}

void SpriteManager::drawChestplate(int col, int row) {
    if (crouching)
        col = 1;
    spritesheet->selectSprite(col, row, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, CHESTPLATE, NO_HELMET);
    spritesheet->drawChestplate(position, flip);
}

void SpriteManager::drawHelmet() {
    spritesheet->selectSprite(2, 0, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE, HELMET);
    spritesheet->drawHelmet(position, flip);
}

SDL2pp::Rect SpriteManager::getPosition(bool isFeather, bool isRightFeather, bool isChestplate,
                                        bool isHelmet) {
    SDL2pp::Rect position = calculateBasePosition();

    if (isFeather) {
        adjustForFeathers(position, isRightFeather);
    } else if (isChestplate) {
        adjustForChestplate(position);
    } else if (isHelmet) {
        adjustForHelmet(position);
    }
    return position;
}

SDL2pp::Rect SpriteManager::calculateBasePosition() {
    return {static_cast<int>(m_position_x - scale), static_cast<int>(m_position_y - scale),
            static_cast<int>(scale * 2), static_cast<int>(scale * 2)};
}

void SpriteManager::adjustForFeathers(SDL2pp::Rect& position, bool isRightFeather) {
    if (isRightFeather) {
        position.x += 0.75 * scale;
    } else {
        position.x += 0.40 * scale;
    }
    if (crouching) {
        position.y += 0.80 * scale;
    } else {
        position.y += 0.70 * scale;
    }

    position.w = 0.9 * scale;
    position.h = 0.9 * scale;
}

void SpriteManager::adjustForHelmet(SDL2pp::Rect& position) {
    if (flip) {
        position.x -= 0.10 * scale;
    } else {
        position.x += 0.10 * scale;
    }
    if (crouching) {
        position.y -= 0.25 * scale;
    } else {
        position.y -= 0.55 * scale;
    }
}

void SpriteManager::adjustForChestplate(SDL2pp::Rect& position) {
    if (flip) {
        position.x -= 0.10 * scale;
    } else {
        position.x += 0.10 * scale;
    }
    if (frame == 0) {
        position.y += 0.14 * scale;
    } else {
        position.y -= 0.20 * scale;
    }
}

void SpriteManager::setScale(float newScale) { scale = newScale; }

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
#define SPRITESHEET_PLAYING_DEAD_COL 1
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
#define DEFAULT_FLAPPING 2
#define LIMIT_FLAPPING_FRAMES 4

#define ROW_WEAPON 3
#define COL_WEAPON 0

#define DEFAULT_ANGLE 0.0
#define UP_ANGLE_RIGHT -90.0
#define UP_ANGLE_LEFT 90.0

SpriteManager::SpriteManager(
        const char* path1, const char* path2,
        SDL2pp::Renderer& renderer /*, int& window_width, int& window_height*/):
        path1(path1),
        path2(path2),
        scale(DEFAULT_SCALE),
        isMoving(false),
        inAir(false),
        crouching(false),
        flapping(false),
        flip(false),
        hasHelmet(false),
        hasChestplate(false),
        shooting(false),
        lookingUp(false),
        gunEquipped(ItemID::CowboyPistol),
        spritesheet(std::make_unique<Spritesheet>(path1, path2, renderer)),
        weaponSpriteManager(std::make_unique<WeaponSpriteManager>()),
        frame(0),
        flappingFrame(DEFAULT_FLAPPING),
        m_position_x(0),
        m_position_y(0) {}

void SpriteManager::updatePosition(float new_x, float new_y) {
    m_position_x = new_x;
    m_position_y = new_y;
}

void SpriteManager::update(const DuckState& state) {
    setFlags(state);

    if (state.beingDamaged) spritesheet->damageEffects(m_position_x, m_position_y);      //estirar frames?

    if (state.inAir) {
        draw(frame, SPRITESHEET_JUMP_ROW, state);
    } else if (state.playingDead || state.crouching) {
        if (state.playingDead) draw(SPRITESHEET_PLAYING_DEAD_COL, SPRITESHEET_DEAD_ROW, state);        //debo borrar feathers. ojos abiertos es banana
        else draw(SPRITESHEET_CROUCH_COL, SPRITESHEET_CROUCH_ROW, state);

    } else {
        draw(frame, SPRITESHEET_RIGHT_LEFT_ROW, state);
    }

    spritesheet->resetDamageEffects();
}

void SpriteManager::updateEquipment(bool helmet, bool chestplate, ItemID& gun) {
    hasHelmet = helmet;
    hasChestplate = chestplate;
    gunEquipped = gun;
}

void SpriteManager::setFlags(const DuckState& state) {
    if (inAir || isMoving) {
        if (!(inAir && frame == 3)) ++frame;
        if (frame > LIMIT_FRAMES && !inAir) frame = 0;
    }
    if (inAir) {
        if (flapping == true) {
            ++flappingFrame;
        } else flapping = true;
    }

    if (state.lookingUp != lookingUp) weaponSpriteManager->setUp();
    
    negateFlag(state.inAir, inAir);
    negateFlag(state.moving, isMoving);
    negateFlag(state.direction == DuckData::Direction::Left, flip);
    negateFlag(state.crouching, crouching);
    negateFlag(state.isShooting, shooting);
    negateFlag(state.lookingUp, lookingUp);

    if (lookingUp) {
        if (!flip) spritesheet->setAngle(UP_ANGLE_RIGHT);
        else spritesheet->setAngle(UP_ANGLE_LEFT);
    }
    else spritesheet->setAngle(DEFAULT_ANGLE);


    if (flapping != state.flapping) {
        flapping = !flapping;
        flappingFrame = DEFAULT_FLAPPING;
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
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_CHESTPLATE, NO_HELMET);
    spritesheet->drawSelectedSprite(position, flip, NO_FEATHER);
}

void SpriteManager::drawFeathers(int col, int row, bool hasWeapon) {
    SDL2pp::Rect position;

    if (hasWeapon) spritesheet->selectSprite(COL_WEAPON, ROW_WEAPON, FEATHER);

    if (flapping && !hasWeapon) {
        if (flappingFrame > LIMIT_FLAPPING_FRAMES) flappingFrame = DEFAULT_FLAPPING;
        drawFlapping();
        return;
    }

    if (!hasWeapon) spritesheet->selectSprite(col, row, FEATHER);

    position = getPosition(FEATHER, NO_CHESTPLATE, NO_HELMET);
    spritesheet->drawSelectedSprite(position, flip, FEATHER);
}


void SpriteManager::drawFlapping() {
    spritesheet->selectSprite(flappingFrame, 2, FEATHER);
    SDL2pp::Rect position = getPosition(FEATHER, NO_CHESTPLATE, NO_HELMET);
    spritesheet->drawSelectedSprite(position, flip, FEATHER);
    flip = !flip;
    position = getPosition(FEATHER, NO_CHESTPLATE, NO_HELMET);
    spritesheet->drawSelectedSprite(position, flip, FEATHER);
    flip = !flip;
}


void SpriteManager::drawChestplate(int col, int row) {
    if (crouching)
        col = 1;
    spritesheet->selectSprite(col, row, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, CHESTPLATE, NO_HELMET);
    spritesheet->drawChestplate(position, flip);
}

void SpriteManager::drawHelmet() {
    spritesheet->selectSprite(2, 0, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_CHESTPLATE, HELMET);
    spritesheet->drawHelmet(position, flip);
}

SDL2pp::Rect SpriteManager::getPosition(bool isFeather, bool isChestplate,
                                        bool isHelmet) {
    SDL2pp::Rect position = calculateBasePosition();

    if (isFeather) {
        adjustForFeathers(position, flip);
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

void SpriteManager::adjustForFeathers(SDL2pp::Rect& position, bool flip) {
    if (!lookingUp) {
        if (flip)
            position.x += 0.75 * scale;
         else
            position.x += 0.40 * scale;

    } else {
        if (flip)
            position.x += 0.50 * scale;
        else
            position.x += 0.60 * scale;
    }

    if (crouching)
        position.y += 0.80 * scale;
    else
        position.y += 0.70 * scale;

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

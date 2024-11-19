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
#define NO_WEAPON false
#define FEATHER true
#define RIGHT_FEATHER true
#define CHESTPLATE true
#define HELMET true
#define WEAPON true

#define OFFSET_RIGHT 3
#define OFFSET_LEFT 3
#define OFFSET_Y 4
#define LIMIT_FRAMES 5

#define ROW_WEAPON 3
#define COL_WEAPON 0

SpriteManager::SpriteManager(
        const char* path1, const char* path2,
        SDL2pp::Renderer& renderer, TextureManager& textureManager /*, int& window_width, int& window_height*/):
        path1(path1),
        path2(path2),
        scale(DEFAULT_SCALE),
        movingRight(false),
        movingLeft(false),
        inAir(false),
        crouching(false),
        flapping(false),
        flip(false),
        hasHelmet(true),
        hasChestplate(true),
        gunEquipped(GunID::CowboyPistol),
        spritesheet(std::make_unique<Spritesheet>(path1, path2, renderer, textureManager)),
        frame(0),
        flappingFrame(0),
        m_position_x(0),
        m_position_y(0) {}

void SpriteManager::updatePosition(float new_x, float new_y) {
    m_position_x = new_x;
    m_position_y = new_y;
}

void SpriteManager::update(const DuckState& state) {
    if (state.movingLeft) flip = true;
    else if (state.movingRight) flip = false;
    setFlags(state);

    if (state.inAir) draw(frame, SPRITESHEET_JUMP_ROW);

    else if (state.beingDamaged || state.playingDead ||
        state.crouching) {
        if (state.beingDamaged) {
            draw(SPRITESHEET_DEAD_COL, SPRITESHEET_DEAD_ROW);
            // do something...? how the game is gonna change for this duck and the others?

        } else if (state.playingDead) {
            draw(SPRITESHEET_PLAYING_DEAD_COL, SPRITESHEET_DEAD_ROW);
        } else {
            draw(SPRITESHEET_CROUCH_COL, SPRITESHEET_CROUCH_ROW);
        }

        } else draw(frame, SPRITESHEET_RIGHT_LEFT_ROW);
}

void SpriteManager::updateEquipment(bool helmet, bool chestplate/*, GunID& gun*/) {
    hasHelmet = helmet;
    hasChestplate = chestplate;
    //gunEquipped = gun;
}

void SpriteManager::setFlags(const DuckState& state) {
    if (inAir || movingRight || movingLeft) {
        if (!(inAir && frame == 4))
            frame++;
        if (frame > LIMIT_FRAMES && !inAir)
            frame = 0;
    }
    if (flapping) {
        flappingFrame++;
        // if (flappingFrame)
    }

    negateFlag(state.inAir, inAir);
    negateFlag(state.movingRight, movingRight);
    negateFlag(state.movingLeft, movingLeft);
    negateFlag(state.crouching, crouching);

    if (flapping != state.flapping) {
        flapping = !flapping;
        frame = 0;
        flappingFrame = 0;
    }
}

void SpriteManager::draw(int col, int row) {
    drawMainSprite(col, row);
    bool hasWeapon = gunEquipped != GunID::NONE;

    if (hasChestplate) drawChestplate(col, row);
    if (hasHelmet) drawHelmet();
    if (gunEquipped != GunID::NONE) drawWeapon();
    drawFeathers(col, row, hasWeapon);
}

void SpriteManager::drawMainSprite(int col, int row) {
    spritesheet->selectSprite(col, row, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE, NO_HELMET, NO_WEAPON);
    spritesheet->drawSelectedSprite(position, flip, NO_FEATHER);
}

void SpriteManager::drawFeathers(int col, int row, bool hasWeapon) {
    if (!flip) {
        if (hasWeapon) spritesheet->selectSprite(COL_WEAPON, ROW_WEAPON, FEATHER);
        else spritesheet->selectSprite(col, row, FEATHER);
        SDL2pp::Rect position = getPosition(FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE, NO_HELMET, NO_WEAPON);
        spritesheet->drawSelectedSprite(position, flip, FEATHER);

    } else if (flip || inAir || flapping) {
        if (hasWeapon) spritesheet->selectSprite(COL_WEAPON, ROW_WEAPON, FEATHER);
        else spritesheet->selectSprite(col, row, FEATHER);
        SDL2pp::Rect position = getPosition(FEATHER, RIGHT_FEATHER, NO_CHESTPLATE, NO_HELMET, NO_WEAPON);
        spritesheet->drawSelectedSprite(position, flip, FEATHER);
    }
}

void SpriteManager::drawChestplate(int col, int row) {
    if (crouching) col = 1;
    spritesheet->selectSprite(col, row, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, CHESTPLATE, NO_HELMET, NO_WEAPON);
    spritesheet->drawChestplate(position, flip);
}

void SpriteManager::drawHelmet() {
    spritesheet->selectSprite(2, 0, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE, HELMET, NO_WEAPON);
    spritesheet->drawHelmet(position, flip);
}

void SpriteManager::drawWeapon() {
    spritesheet->selectSprite(0, 0, NO_FEATHER);
    SDL2pp::Rect position = getPosition(NO_FEATHER, NO_RIGHT_FEATHER, NO_CHESTPLATE, NO_HELMET, WEAPON);

    std::string path = gunPaths[gunEquipped];
    spritesheet->drawWeapon(position, flip, path);
}

void SpriteManager::negateFlag(bool flag, bool& flagToNegate) {
    if (flagToNegate != flag) {
        flagToNegate = !flagToNegate;
        frame = 0;
    }
}

SDL2pp::Rect SpriteManager::getPosition(bool isFeather, bool isRightFeather, bool isChestplate, bool isHelmet, bool isWeapon) {
    SDL2pp::Rect position = calculateBasePosition();
    int spriteHeight = spritesheet->getClipHeight();

    if (isFeather) adjustForFeathers(position, isRightFeather);
    if (isChestplate) if (frame == 0) position.y += (spriteHeight / 2) * scale / DEFAULT_SCALE;
    if (isHelmet) adjustForHelmet(position);
    if (isWeapon) adjustForWeapon(position);

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
    if (crouching) position.y += 48 * scale / DEFAULT_SCALE;
    else position.y += (spriteHeight * 2 + OFFSET_Y) * scale / DEFAULT_SCALE;
}

void SpriteManager::adjustForHelmet(SDL2pp::Rect& position) {
    if (flip) position.x -= /*frame*/ 2 * scale / DEFAULT_SCALE;
    else position.x += /*frame*/ 2 * scale / DEFAULT_SCALE;
    if (crouching) position.y += 3 * scale / DEFAULT_SCALE;
    else position.y -= 14 * scale / DEFAULT_SCALE;
}

void SpriteManager::adjustForWeapon(SDL2pp::Rect& position) {
    int spriteWidth = spritesheet->getClipWidth();
    int spriteHeight = spritesheet->getClipHeight();

    if (flip) position.x -= (spriteWidth / 2) + 2 * scale / DEFAULT_SCALE;
    else position.x += (spriteHeight / 2) + 2 * scale / DEFAULT_SCALE;

    if (crouching) position.y += 20 * scale / DEFAULT_SCALE;
    else position.y += 8 * scale / DEFAULT_SCALE;
}

Spritesheet& SpriteManager::getSpritesheet() {return *spritesheet;}

void SpriteManager::setScale(float newScale) {
    scale = newScale;
}

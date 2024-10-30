#include "Player.h"

/*#define DEFAULT_SCALE 2.5f
#define DEFAULT_OFFSET_Y 200
#define SPRITESHEET_UP 0
#define SPRITESHEET_DOWN 1
#define SPRITESHEET_LEFT 0
#define SPRITESHEET_RIGHT 0
#define SPRITESHEET_JUMP 1

#define SPRITESHEET_DOWN_COL 5

#define SPRITE_IDLE 0
#define JUMP_FRAMES 5
#define GRAVITY 9.8
#define JUMP_VELOCITY 500.0
#define DELTA_TIME (1.0/30.0)

Player::Player(const char* path, int row, int column, SDL2pp::Renderer& renderer, int window_width,
int window_height) : last_m_key(Keybinds::NONE), scale(DEFAULT_SCALE), flip(false),
is_jumping(false), jump_frame(0), jump_velocity(0), jump_start_y(0),
    m_spritesheet_column(SPRITE_IDLE), window_width(window_width), window_height(window_height),
renderer(renderer), spritesheet(path, row, column, renderer) {

    int playerWidth = spritesheet.getClipWidth();
    int playerHeight = spritesheet.getClipHeight();
    m_position_x = (window_width - playerWidth * scale) / 2;
    m_position_y = (window_height - playerHeight * scale) / 2 + DEFAULT_OFFSET_Y;
}

Player::~Player() {
}

void Player::start() {
    spritesheet.select_sprite(SPRITE_IDLE, SPRITE_IDLE);
    SDL2pp::Rect position = getPosition();
    spritesheet.draw_selected_sprite(renderer, position, flip);
}

void Player::update(Keybinds m_key) {
    double m_x = m_position_x;
    double m_y = m_position_y;

    switch(m_key) {
        case Keybinds::NONE:
            spritesheet.select_sprite(SPRITE_IDLE, SPRITE_IDLE);
            break;
        case Keybinds::UP:
            // CAMBIA LA PUNTERIA DE ARMA ETC...?
            break;
        case Keybinds::DOWN:
            spritesheet.select_sprite(SPRITESHEET_DOWN_COL, SPRITESHEET_DOWN);
            break;
        case Keybinds::LEFT:
            m_x = m_x - (500.0 * DELTA_TIME);
            spritesheet.select_sprite(m_spritesheet_column, SPRITESHEET_LEFT);
            flip = true;
            break;
        case Keybinds::RIGHT:
            m_x = m_x + (500.0 * DELTA_TIME);
            spritesheet.select_sprite(m_spritesheet_column, SPRITESHEET_RIGHT);
            flip = false;
            break;
        case Keybinds::JUMP:
            if (!is_jumping) {
                is_jumping = true;
                jump_velocity = JUMP_VELOCITY;
                jump_start_y = m_y;
                jump_frame = 0;
            }
            break;
    }

    if (is_jumping)
        m_y = jumpLogic(m_y);

    m_position_x = m_x;
    m_position_y = m_y;

    if (m_key != Keybinds::NONE && m_key != Keybinds::DOWN && m_key != Keybinds::UP) {
        m_spritesheet_column++;
    }

    if (m_spritesheet_column > 6) {
        m_spritesheet_column = 1;
        spritesheet.select_sprite(SPRITE_IDLE, SPRITE_IDLE);
    }

    last_m_key = m_key;

    SDL2pp::Rect position = getPosition();
    spritesheet.draw_selected_sprite(renderer, position, flip);
}

double Player::jumpLogic(double m_y) {
    jump_velocity -= GRAVITY * DELTA_TIME * 100;
    m_y -= jump_velocity * DELTA_TIME;

    if (m_y >= jump_start_y) {
        m_y = jump_start_y;
        is_jumping = false;
        jump_frame = 0;
    } else {
        if (jump_frame < JUMP_FRAMES) {
            spritesheet.select_sprite(jump_frame, SPRITESHEET_JUMP);
            jump_frame++;
        }
    }
    return m_y;
}

SDL2pp::Rect Player::getPosition() {
    int playerWidth = spritesheet.getClipWidth();
    int playerHeight = spritesheet.getClipHeight();
    SDL2pp::Rect position(m_position_x, m_position_y, playerWidth * scale, playerHeight * scale);
    return position;
}*/

#include <limits>
#include <utility>

#include "Config.h"

#define GRENADE "grenade"
#define BANANA "banana"
#define PEW_PEW_LASER "pew pew laser"
#define LASER_RIFLE "laser rifle"
#define AK_47 "ak-47"
#define DUEL_PISTOL "duel pistol"
#define COWBOY_PISTOL "cowboy pistol"
#define MAGNUM "magnum"
#define SHOTGUN "shotgun"
#define SNIPER "sniper"
#define HELMET "helmet"
#define ARMOR "armor"
#define NOTHING "nothing"

const HashMap<std::string, ItemID> Config::itemIDs = {{GRENADE, ItemID::Grenade},
                                                            {BANANA, ItemID::Banana},
                                                            {PEW_PEW_LASER, ItemID::PewPewLaser},
                                                            {LASER_RIFLE, ItemID::LaserRifle},
                                                            {AK_47, ItemID::Ak47},
                                                            {DUEL_PISTOL, ItemID::DuelPistol},
                                                            {COWBOY_PISTOL, ItemID::CowboyPistol},
                                                            {MAGNUM, ItemID::Magnum},
                                                            {SHOTGUN, ItemID::Shotgun},
                                                            {SNIPER, ItemID::Sniper},
                                                            {HELMET, ItemID::Helmet},
                                                            {ARMOR, ItemID::Armor},
                                                            {NOTHING, ItemID::NONE}};

std::string Config::configDirectory{"/etc/DuckGame/"};     // NOLINT(runtime/string)
std::string Config::mapsDirectory_{"/etc/DuckGame/maps"};  // NOLINT(runtime/string)

float Config::Duck::jumpTime_{};
float Config::Duck::acceleration_{};
float Config::Duck::airAcceleration_{};
float Config::Duck::minSpeed_{};
float Config::Duck::maxSpeed_{};
float Config::Duck::jumpSpeed_{};
ItemID Config::Duck::defaultWeapon_{ItemID::NONE};
bool Config::Duck::defaultArmor_{};
bool Config::Duck::defaultHelmet_{};

float Config::Physics::gravity_{};

float Config::Weapons::minSpawnTime_{};
float Config::Weapons::maxSpawnTime_{};

u8 Config::Weapons::Grenade::ammo_{};
float Config::Weapons::Grenade::reach_{};
float Config::Weapons::Grenade::radius_{};
float Config::Weapons::Grenade::explosionTime_{};

u8 Config::Weapons::Banana::ammo_{};
float Config::Weapons::Banana::reach_{};

u8 Config::Weapons::PewPewLaser::ammo_{};
float Config::Weapons::PewPewLaser::dispersion_{};
Vector2 Config::Weapons::PewPewLaser::recoil_{};
float Config::Weapons::PewPewLaser::minReach_{};
float Config::Weapons::PewPewLaser::maxReach_{};
u8 Config::Weapons::PewPewLaser::raysPerShot_{};

u8 Config::Weapons::LaserRifle::ammo_{};
float Config::Weapons::LaserRifle::reach_{};
float Config::Weapons::LaserRifle::dispersion_{};
Vector2 Config::Weapons::LaserRifle::recoil_{};
float Config::Weapons::LaserRifle::timeBetweenShots_{};
float Config::Weapons::LaserRifle::rayAngle_{};
u8 Config::Weapons::LaserRifle::bounces_{};

u8 Config::Weapons::Ak47::ammo_{};
float Config::Weapons::Ak47::reach_{};
Vector2 Config::Weapons::Ak47::recoil_{};
float Config::Weapons::Ak47::timeBetweenShots_{};
float Config::Weapons::Ak47::minDispersion_{};
float Config::Weapons::Ak47::midDispersion_{};
float Config::Weapons::Ak47::maxDispersion_{};

u8 Config::Weapons::DuelPistol::ammo_{};
float Config::Weapons::DuelPistol::reach_{};
float Config::Weapons::DuelPistol::dispersion_{};
Vector2 Config::Weapons::DuelPistol::recoil_{};

u8 Config::Weapons::CowboyPistol::ammo_{};
float Config::Weapons::CowboyPistol::reach_{};
float Config::Weapons::CowboyPistol::dispersion_{};
Vector2 Config::Weapons::CowboyPistol::recoil_{};

u8 Config::Weapons::Magnum::ammo_{};
float Config::Weapons::Magnum::reach_{};
float Config::Weapons::Magnum::dispersion_{};
Vector2 Config::Weapons::Magnum::recoil_{};

u8 Config::Weapons::Shotgun::ammo_{};
float Config::Weapons::Shotgun::dispersion_{};
Vector2 Config::Weapons::Shotgun::recoil_{};
float Config::Weapons::Shotgun::minReach_{};
float Config::Weapons::Shotgun::maxReach_{};
u8 Config::Weapons::Shotgun::pelletsPerShot_{};
float Config::Weapons::Shotgun::reloadTime_{};

u8 Config::Weapons::Sniper::ammo_{};
float Config::Weapons::Sniper::reach_{};
float Config::Weapons::Sniper::dispersion_{};
Vector2 Config::Weapons::Sniper::recoil_{};
float Config::Weapons::Sniper::reloadTime_{};

u8 Config::Armor::armor_{};
u8 Config::Armor::helmet_{};

u8 Config::Match::rounds_{};
u8 Config::Match::pointsToWin_{};

Config::BadConfigFile::BadConfigFile(const std::string& message):
        std::runtime_error(message) {}

void Config::setConfigPath(std::string path) { configDirectory = std::move(path); }
void Config::setMapsDirectory(std::string maps) { mapsDirectory_ = std::move(maps); }

const std::string& Config::mapsDirectory() { return mapsDirectory_; }

#define X_COORD "x"
#define Y_COORD "y"

template <>
struct YAML::convert<Vector2> {
    static Node encode(const Vector2& rhs) {
        Node node;
        node[X_COORD] = rhs.x();
        node[Y_COORD] = rhs.y();
        return node;
    }

    static bool decode(const Node& node, Vector2& rhs) {
        if (!node.IsMap())
            return false;
        rhs.setX(node[X_COORD].as<float>());
        rhs.setY(node[Y_COORD].as<float>());
        return true;
    }
};

void Config::load() {
    using YAML::Node, YAML::LoadFile, YAML::BadFile, YAML::ParserException;

    Duck::load();
    Physics::load();
    Weapons::load();
    Weapons::Grenade::load();
    Weapons::Banana::load();
    Weapons::PewPewLaser::load();
    Weapons::LaserRifle::load();
    Weapons::Ak47::load();
    Weapons::DuelPistol::load();
    Weapons::CowboyPistol::load();
    Weapons::Magnum::load();
    Weapons::Shotgun::load();
    Weapons::Sniper::load();
    Armor::load();
    Match::load();
}

#define FLOAT "float"
#define U8 "u8"
#define BOOL "bool"
#define STRING "string"
#define OR "or a"
#define VALID_WEAPON "valid weapon"

#define COULD_NOT_OPEN_FILE "Could not open the configuration file at "
#define CONFIG_FILE_AT "The configuration file at "
#define NOT_VALID " is not a valid YAML file"

#define DUCK "duck"

#define JUMP_TIME "jump time"
#define ACCELERATION "acceleration"
#define AIR_ACCELERATION "air acceleration"
#define MIN_SPEED "min speed"
#define MAX_SPEED "max speed"
#define JUMP_SPEED "jump speed"
#define DEFAULT_HAND_ITEM "default hand item"
#define INVALID_WEAPON "duck -> default weapon in config file is not a valid weapon"
#define DEFAULT_ARMOR "default armor"
#define DEFAULT_HELMET "default helmet"

#define DUCK_CONFIG_FILE "config/duck.yaml"
#define PARSING_ERROR_BEGIN "Error while parsing"
#define PARSING_ERROR_END "Either it's missing in the config/duck.yaml file or it's not a"

#define JUMP_TIME_ERROR PARSING_ERROR_BEGIN " " DUCK " " JUMP_TIME ". " PARSING_ERROR_END " " FLOAT
#define ACCELERATION_ERROR \
    PARSING_ERROR_BEGIN " " DUCK " " ACCELERATION ". " PARSING_ERROR_END " " FLOAT
#define AIR_ACCELERATION_ERROR \
    PARSING_ERROR_BEGIN " " DUCK " " AIR_ACCELERATION ". " PARSING_ERROR_END " " FLOAT
#define MIN_SPEED_ERROR PARSING_ERROR_BEGIN " " DUCK " " MIN_SPEED ". " PARSING_ERROR_END " " FLOAT
#define MAX_SPEED_ERROR PARSING_ERROR_BEGIN " " DUCK " " MAX_SPEED ". " PARSING_ERROR_END " " FLOAT
#define JUMP_SPEED_ERROR \
    PARSING_ERROR_BEGIN " " DUCK " " JUMP_SPEED ". " PARSING_ERROR_END " " FLOAT
#define DEFAULT_HAND_ITEM_ERROR                                                                 \
    PARSING_ERROR_BEGIN " " DUCK " " DEFAULT_HAND_ITEM ". " PARSING_ERROR_END " " STRING " " OR \
                        " " VALID_WEAPON
#define DEFAULT_ARMOR_ERROR \
    PARSING_ERROR_BEGIN " " DUCK " " DEFAULT_ARMOR ". " PARSING_ERROR_END " bool"
#define DEFAULT_HELMET_ERROR \
    PARSING_ERROR_BEGIN " " DUCK " " DEFAULT_HELMET ". " PARSING_ERROR_END " bool"

#define JUMP_TIME_BAD_VALUE "Jump time must be greater or equal than 0"
#define ACCELERATION_BAD_VALUE "Acceleration must be greater or equal than 0"
#define AIR_ACCELERATION_BAD_VALUE "Air acceleration must be greater or equal than 0"
#define MIN_SPEED_BAD_VALUE "Minimum speed must be greater or equal than 0"
#define MAX_SPEED_BAD_VALUE "Maximum speed must be greater or equal than 0"
#define JUMP_SPEED_BAD_VALUE "Jump speed must be greater or equal than 0"

void Config::Duck::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + DUCK_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + DUCK_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + DUCK_CONFIG_FILE + NOT_VALID);
    }

    try {
        jumpTime_ = config[JUMP_TIME].as<float>();
        if (jumpTime_ < 0)
            throw BadConfigFile(JUMP_TIME_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(JUMP_TIME_ERROR);
    }

    try {
        acceleration_ = config[ACCELERATION].as<float>();
        if (acceleration_ < 0)
            throw BadConfigFile(ACCELERATION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(ACCELERATION_ERROR);
    }

    try {
        airAcceleration_ = config[AIR_ACCELERATION].as<float>();
        if (airAcceleration_ < 0)
            throw BadConfigFile(AIR_ACCELERATION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(AIR_ACCELERATION_ERROR);
    }

    try {
        minSpeed_ = config[MIN_SPEED].as<float>();
        if (minSpeed_ < 0)
            throw BadConfigFile(MIN_SPEED_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(MIN_SPEED_ERROR);
    }

    try {
        maxSpeed_ = config[MAX_SPEED].as<float>();
        if (maxSpeed_ < 0)
            throw BadConfigFile(MAX_SPEED_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(MAX_SPEED_ERROR);
    }

    try {
        jumpSpeed_ = config[JUMP_SPEED].as<float>();
        if (jumpSpeed_ < 0)
            throw BadConfigFile(JUMP_SPEED_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(JUMP_SPEED_ERROR);
    }

    try {
        defaultWeapon_ = itemIDs.at(config[DEFAULT_HAND_ITEM].as<std::string>());
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(DEFAULT_HAND_ITEM_ERROR);
    } catch (const std::out_of_range& _) {
        throw BadConfigFile(INVALID_WEAPON);
    }

    try {
        defaultArmor_ = config[DEFAULT_ARMOR].as<bool>();
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(DEFAULT_ARMOR_ERROR);
    }

    try {
        defaultHelmet_ = config[DEFAULT_HELMET].as<bool>();
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(DEFAULT_HELMET_ERROR);
    }
}

#define PHYSICS "physics"
#define GRAVITY "gravity"
#define PHYSICS_CONFIG_FILE "config/physics.yaml"
#define GRAVITY_ERROR PARSING_ERROR_BEGIN " " PHYSICS " " GRAVITY ". " PARSING_ERROR_END " " FLOAT
#define GRAVITY_BAD_VALUE "Gravity must be greater or equal than 0"

void Config::Physics::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + PHYSICS_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + PHYSICS_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + PHYSICS_CONFIG_FILE + NOT_VALID);
    }

    try {
        gravity_ = config[GRAVITY].as<float>();
        if (gravity_ < 0)
            throw BadConfigFile(GRAVITY_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(GRAVITY_ERROR);
    }
}

#define WEAPONS "weapons"

#define MIN_SPAWN_TIME "min spawn time"
#define MAX_SPAWN_TIME "max spawn time"

#define WEAPONS_CONFIG_FILE "config/weapons.yaml"

#define MIN_SPAWN_TIME_ERROR \
    PARSING_ERROR_BEGIN " " WEAPONS " " MIN_SPAWN_TIME ". " PARSING_ERROR_END " " FLOAT

#define MAX_SPAWN_TIME_ERROR \
    PARSING_ERROR_BEGIN " " WEAPONS " " MAX_SPAWN_TIME ". " PARSING_ERROR_END " " FLOAT

void Config::Weapons::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + WEAPONS_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + WEAPONS_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + WEAPONS_CONFIG_FILE + NOT_VALID);
    }

    try {
        minSpawnTime_ = config[MIN_SPAWN_TIME].as<float>();
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(MIN_SPAWN_TIME_ERROR);
    }

    try {
        maxSpawnTime_ = config[MAX_SPAWN_TIME].as<float>();
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(MAX_SPAWN_TIME_ERROR);
    }
}

#define AMMO "ammo"
#define REACH "reach"
#define RADIUS "radius"
#define EXPLOSION_TIME "explosion time"

#define GRENADE_CONFIG_FILE "config/weapons/grenade.yaml"

#define GRENADE_AMMO_ERROR PARSING_ERROR_BEGIN " " GRENADE " " AMMO ". " PARSING_ERROR_END " " U8
#define GRENADE_REACH_ERROR \
    PARSING_ERROR_BEGIN " " GRENADE " " REACH ". " PARSING_ERROR_END " " FLOAT
#define GRENADE_RADIUS_ERROR \
    PARSING_ERROR_BEGIN " " GRENADE " " RADIUS ". " PARSING_ERROR_END " " FLOAT
#define GRENADE_EXPLOSION_TIME_ERROR \
    PARSING_ERROR_BEGIN " " GRENADE " " EXPLOSION_TIME ". " PARSING_ERROR_END " " FLOAT

#define REACH_BAD_VALUE "Reach must be greater or equal than 0"
#define RADIUS_BAD_VALUE "Radius must be greater or equal than 0"
#define EXPLOSION_TIME_BAD_VALUE "Explosion time must be greater or equal than 0"

void Config::Weapons::Grenade::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + GRENADE_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + GRENADE_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + GRENADE_CONFIG_FILE + NOT_VALID);
    }

    try {
        const int _ammo = config[AMMO].as<int>();
        if (_ammo < std::numeric_limits<u8>::min() or _ammo > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        ammo_ = _ammo;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(GRENADE_AMMO_ERROR);
    }

    try {
        reach_ = config[REACH].as<float>();
        if (reach_ < 0)
            throw BadConfigFile(REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(GRENADE_REACH_ERROR);
    }

    try {
        radius_ = config[RADIUS].as<float>();
        if (radius_ < 0)
            throw BadConfigFile(RADIUS_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(GRENADE_RADIUS_ERROR);
    }

    try {
        explosionTime_ = config[EXPLOSION_TIME].as<float>();
        if (explosionTime_ < 0)
            throw BadConfigFile(EXPLOSION_TIME_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(GRENADE_EXPLOSION_TIME_ERROR);
    }
}

#define BANANA_CONFIG_FILE "config/weapons/banana.yaml"

#define BANANA_AMMO_ERROR PARSING_ERROR_BEGIN " " BANANA " " AMMO ". " PARSING_ERROR_END " " U8
#define BANANA_REACH_ERROR PARSING_ERROR_BEGIN " " BANANA " " REACH ". " PARSING_ERROR_END " " FLOAT

void Config::Weapons::Banana::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + BANANA_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + BANANA_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + BANANA_CONFIG_FILE + NOT_VALID);
    }

    try {
        const int _ammo = config[AMMO].as<int>();
        if (_ammo < std::numeric_limits<u8>::min() or _ammo > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        ammo_ = _ammo;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(BANANA_AMMO_ERROR);
    }

    try {
        reach_ = config[REACH].as<float>();
        if (reach_ < 0)
            throw BadConfigFile(REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(BANANA_REACH_ERROR);
    }
}

#define DISPERSION "dispersion"
#define RECOIL "recoil"
#define MIN_REACH "min reach"
#define MAX_REACH "max reach"
#define RAYS_PER_SHOT "rays per shot"

#define PEW_PEW_LASER_CONFIG_FILE "config/weapons/pew_pew_laser.yaml"

#define PEW_PEW_LASER_AMMO_ERROR \
    PARSING_ERROR_BEGIN " " PEW_PEW_LASER " " AMMO ". " PARSING_ERROR_END " " U8
#define PEW_PEW_LASER_DISPERSION_ERROR \
    PARSING_ERROR_BEGIN " " PEW_PEW_LASER " " DISPERSION ". " PARSING_ERROR_END " " FLOAT
#define PEW_PEW_LASER_RECOIL_ERROR \
    PARSING_ERROR_BEGIN " " PEW_PEW_LASER " " RECOIL ". " PARSING_ERROR_END " " FLOAT
#define PEW_PEW_LASER_MIN_REACH_ERROR \
    PARSING_ERROR_BEGIN " " PEW_PEW_LASER " " MIN_REACH ". " PARSING_ERROR_END " " FLOAT
#define PEW_PEW_LASER_MAX_REACH_ERROR \
    PARSING_ERROR_BEGIN " " PEW_PEW_LASER " " MAX_REACH ". " PARSING_ERROR_END " " FLOAT
#define PEW_PEW_LASER_RAYS_PER_SHOT_ERROR \
    PARSING_ERROR_BEGIN " " PEW_PEW_LASER " " RAYS_PER_SHOT ". " PARSING_ERROR_END " " U8

#define DISPERSION_BAD_VALUE "Dispersion must be greater or equal than 0"
#define RECOIL_BAD_VALUE "Recoil x and y values must be greater or equal than 0"
#define MIN_REACH_BAD_VALUE "Minimum reach must be greater or equal than 0"
#define MAX_REACH_BAD_VALUE "Maximum reach must be greater or equal than 0"

void Config::Weapons::PewPewLaser::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + PEW_PEW_LASER_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + PEW_PEW_LASER_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + PEW_PEW_LASER_CONFIG_FILE +
                            NOT_VALID);
    }

    try {
        const int _ammo = config[AMMO].as<int>();
        if (_ammo < std::numeric_limits<u8>::min() or _ammo > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        ammo_ = _ammo;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(PEW_PEW_LASER_AMMO_ERROR);
    }

    try {
        dispersion_ = config[DISPERSION].as<float>();
        if (dispersion_ < 0)
            throw BadConfigFile(DISPERSION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(PEW_PEW_LASER_DISPERSION_ERROR);
    }

    try {
        recoil_ = config[RECOIL].as<Vector2>();
        if (recoil_.x() < 0 or recoil_.y() < 0)
            throw BadConfigFile(RECOIL_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(PEW_PEW_LASER_RECOIL_ERROR);
    }

    try {
        minReach_ = config[MIN_REACH].as<float>();
        if (minReach_ < 0)
            throw BadConfigFile(MIN_REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(PEW_PEW_LASER_MIN_REACH_ERROR);
    }

    try {
        maxReach_ = config[MAX_REACH].as<float>();
        if (maxReach_ < 0)
            throw BadConfigFile(MAX_REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(PEW_PEW_LASER_MAX_REACH_ERROR);
    }

    try {
        const int _raysPerShot = config[RAYS_PER_SHOT].as<int>();
        if (_raysPerShot < std::numeric_limits<u8>::min() or
            _raysPerShot > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        raysPerShot_ = _raysPerShot;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(PEW_PEW_LASER_RAYS_PER_SHOT_ERROR);
    }
}

#define TIME_BETWEEN_SHOTS "time between shots"
#define RAY_ANGLE "ray angle"
#define BOUNCES "bounces"

#define LASER_RIFLE_CONFIG_FILE "config/weapons/laser_rifle.yaml"

#define LASER_RIFLE_AMMO_ERROR \
    PARSING_ERROR_BEGIN " " LASER_RIFLE " " AMMO ". " PARSING_ERROR_END " " U8
#define LASER_RIFLE_REACH_ERROR \
    PARSING_ERROR_BEGIN " " LASER_RIFLE " " REACH ". " PARSING_ERROR_END " " FLOAT
#define LASER_RIFLE_DISPERSION_ERROR \
    PARSING_ERROR_BEGIN " " LASER_RIFLE " " DISPERSION ". " PARSING_ERROR_END " " FLOAT
#define LASER_RIFLE_RECOIL_ERROR \
    PARSING_ERROR_BEGIN " " LASER_RIFLE " " RECOIL ". " PARSING_ERROR_END " " FLOAT
#define LASER_RIFLE_TIME_BETWEEN_SHOTS_ERROR \
    PARSING_ERROR_BEGIN " " LASER_RIFLE " " TIME_BETWEEN_SHOTS ". " PARSING_ERROR_END " " FLOAT
#define LASER_RIFLE_RAY_ANGLE_ERROR \
    PARSING_ERROR_BEGIN " " LASER_RIFLE " " RAY_ANGLE ". " PARSING_ERROR_END " " FLOAT
#define LASER_RIFLE_BOUNCES_ERROR \
    PARSING_ERROR_BEGIN " " LASER_RIFLE " " BOUNCES ". " PARSING_ERROR_END " " U8

#define TIME_BETWEEN_SHOTS_BAD_VALUE "Time between shots must be greater or equal than 0"
#define RAY_ANGLE_BAD_VALUE "Ray angle must be greater or equal than 0"
#define BOUNCES_BAD_VALUE "Bounces must be greater or equal than 0"

void Config::Weapons::LaserRifle::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + LASER_RIFLE_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + LASER_RIFLE_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + LASER_RIFLE_CONFIG_FILE + NOT_VALID);
    }

    try {
        const int _ammo = config[AMMO].as<int>();
        if (_ammo < std::numeric_limits<u8>::min() or _ammo > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        ammo_ = _ammo;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(LASER_RIFLE_AMMO_ERROR);
    }

    try {
        reach_ = config[REACH].as<float>();
        if (reach_ < 0)
            throw BadConfigFile(REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(LASER_RIFLE_REACH_ERROR);
    }

    try {
        dispersion_ = config[DISPERSION].as<float>();
        if (dispersion_ < 0)
            throw BadConfigFile(DISPERSION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(LASER_RIFLE_DISPERSION_ERROR);
    }

    try {
        recoil_ = config[RECOIL].as<Vector2>();
        if (recoil_.x() < 0 or recoil_.y() < 0)
            throw BadConfigFile(RECOIL_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(LASER_RIFLE_RECOIL_ERROR);
    }

    try {
        timeBetweenShots_ = config[TIME_BETWEEN_SHOTS].as<float>();
        if (timeBetweenShots_ < 0)
            throw BadConfigFile(TIME_BETWEEN_SHOTS_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(LASER_RIFLE_TIME_BETWEEN_SHOTS_ERROR);
    }

    try {
        rayAngle_ = config[RAY_ANGLE].as<float>();
        if (rayAngle_ < 0)
            throw BadConfigFile(RAY_ANGLE_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(LASER_RIFLE_RAY_ANGLE_ERROR);
    }

    try {
        const int _bounces = config[BOUNCES].as<int>();
        if (_bounces < std::numeric_limits<u8>::min() or _bounces > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        bounces_ = _bounces;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(LASER_RIFLE_BOUNCES_ERROR);
    }
}

#define MIN_DISPERSION "min dispersion"
#define MID_DISPERSION "mid dispersion"
#define MAX_DISPERSION "max dispersion"

#define AK_47_CONFIG_FILE "config/weapons/ak_47.yaml"

#define AK_47_AMMO_ERROR PARSING_ERROR_BEGIN " " AK_47 " " AMMO ". " PARSING_ERROR_END " " U8
#define AK_47_REACH_ERROR PARSING_ERROR_BEGIN " " AK_47 " " REACH ". " PARSING_ERROR_END " " FLOAT
#define AK_47_RECOIL_ERROR PARSING_ERROR_BEGIN " " AK_47 " " RECOIL ". " PARSING_ERROR_END " " FLOAT
#define AK_47_TIME_BETWEEN_SHOTS_ERROR \
    PARSING_ERROR_BEGIN " " AK_47 " " TIME_BETWEEN_SHOTS ". " PARSING_ERROR_END " " FLOAT
#define AK_47_MIN_DISPERSION_ERROR \
    PARSING_ERROR_BEGIN " " AK_47 " " MIN_DISPERSION ". " PARSING_ERROR_END " " FLOAT
#define AK_47_MID_DISPERSION_ERROR \
    PARSING_ERROR_BEGIN " " AK_47 " " MID_DISPERSION ". " PARSING_ERROR_END " " FLOAT
#define AK_47_MAX_DISPERSION_ERROR \
    PARSING_ERROR_BEGIN " " AK_47 " " MAX_DISPERSION ". " PARSING_ERROR_END " " FLOAT

#define MIN_DISPERSION_BAD_VALUE "Minimum dispersion must be greater or equal than 0"
#define MID_DISPERSION_BAD_VALUE "Mid dispersion must be greater or equal than 0"
#define MAX_DISPERSION_BAD_VALUE "Maximum dispersion must be greater or equal than 0"

void Config::Weapons::Ak47::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + AK_47_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + AK_47_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + AK_47_CONFIG_FILE + NOT_VALID);
    }

    try {
        const int _ammo = config[AMMO].as<int>();
        if (_ammo < std::numeric_limits<u8>::min() or _ammo > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        ammo_ = _ammo;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(AK_47_AMMO_ERROR);
    }

    try {
        reach_ = config[REACH].as<float>();
        if (reach_ < 0)
            throw BadConfigFile(REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(AK_47_REACH_ERROR);
    }

    try {
        recoil_ = config[RECOIL].as<Vector2>();
        if (recoil_.x() < 0 or recoil_.y() < 0)
            throw BadConfigFile(RECOIL_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(AK_47_RECOIL_ERROR);
    }

    try {
        timeBetweenShots_ = config[TIME_BETWEEN_SHOTS].as<float>();
        if (timeBetweenShots_ < 0)
            throw BadConfigFile(TIME_BETWEEN_SHOTS_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(AK_47_TIME_BETWEEN_SHOTS_ERROR);
    }

    try {
        minDispersion_ = config[MIN_DISPERSION].as<float>();
        if (minDispersion_ < 0)
            throw BadConfigFile(MIN_DISPERSION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(AK_47_MIN_DISPERSION_ERROR);
    }

    try {
        midDispersion_ = config[MID_DISPERSION].as<float>();
        if (midDispersion_ < 0)
            throw BadConfigFile(MID_DISPERSION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(AK_47_MID_DISPERSION_ERROR);
    }

    try {
        maxDispersion_ = config[MAX_DISPERSION].as<float>();
        if (maxDispersion_ < 0)
            throw BadConfigFile(MAX_DISPERSION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(AK_47_MAX_DISPERSION_ERROR);
    }
}

#define DUEL_PISTOL_CONFIG_FILE "config/weapons/duel_pistol.yaml"

#define DUEL_PISTOL_AMMO_ERROR \
    PARSING_ERROR_BEGIN " " DUEL_PISTOL " " AMMO ". " PARSING_ERROR_END " " U8
#define DUEL_PISTOL_REACH_ERROR \
    PARSING_ERROR_BEGIN " " DUEL_PISTOL " " REACH ". " PARSING_ERROR_END " " FLOAT
#define DUEL_PISTOL_DISPERSION_ERROR \
    PARSING_ERROR_BEGIN " " DUEL_PISTOL " " DISPERSION ". " PARSING_ERROR_END " " FLOAT
#define DUEL_PISTOL_RECOIL_ERROR \
    PARSING_ERROR_BEGIN " " DUEL_PISTOL " " RECOIL ". " PARSING_ERROR_END " " FLOAT

void Config::Weapons::DuelPistol::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + DUEL_PISTOL_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + DUEL_PISTOL_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + DUEL_PISTOL_CONFIG_FILE + NOT_VALID);
    }

    try {
        const int _ammo = config[AMMO].as<int>();
        if (_ammo < std::numeric_limits<u8>::min() or _ammo > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        ammo_ = _ammo;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(DUEL_PISTOL_AMMO_ERROR);
    }

    try {
        reach_ = config[REACH].as<float>();
        if (reach_ < 0)
            throw BadConfigFile(REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(DUEL_PISTOL_REACH_ERROR);
    }

    try {
        dispersion_ = config[DISPERSION].as<float>();
        if (dispersion_ < 0)
            throw BadConfigFile(DISPERSION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(DUEL_PISTOL_DISPERSION_ERROR);
    }

    try {
        recoil_ = config[RECOIL].as<Vector2>();
        if (recoil_.x() < 0 or recoil_.y() < 0)
            throw BadConfigFile(RECOIL_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(DUEL_PISTOL_RECOIL_ERROR);
    }
}

#define COWBOY_PISTOL_CONFIG_FILE "config/weapons/cowboy_pistol.yaml"

#define COWBOY_PISTOL_AMMO_ERROR \
    PARSING_ERROR_BEGIN " " COWBOY_PISTOL " " AMMO ". " PARSING_ERROR_END " " U8
#define COWBOY_PISTOL_REACH_ERROR \
    PARSING_ERROR_BEGIN " " COWBOY_PISTOL " " REACH ". " PARSING_ERROR_END " " FLOAT
#define COWBOY_PISTOL_DISPERSION_ERROR \
    PARSING_ERROR_BEGIN " " COWBOY_PISTOL " " DISPERSION ". " PARSING_ERROR_END " " FLOAT
#define COWBOY_PISTOL_RECOIL_ERROR \
    PARSING_ERROR_BEGIN " " COWBOY_PISTOL " " RECOIL ". " PARSING_ERROR_END " " FLOAT

void Config::Weapons::CowboyPistol::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + COWBOY_PISTOL_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + COWBOY_PISTOL_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + COWBOY_PISTOL_CONFIG_FILE +
                            NOT_VALID);
    }

    try {
        const int _ammo = config[AMMO].as<int>();
        if (_ammo < std::numeric_limits<u8>::min() or _ammo > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        ammo_ = _ammo;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(COWBOY_PISTOL_AMMO_ERROR);
    }

    try {
        reach_ = config[REACH].as<float>();
        if (reach_ < 0)
            throw BadConfigFile(REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(COWBOY_PISTOL_REACH_ERROR);
    }

    try {
        dispersion_ = config[DISPERSION].as<float>();
        if (dispersion_ < 0)
            throw BadConfigFile(DISPERSION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(COWBOY_PISTOL_DISPERSION_ERROR);
    }

    try {
        recoil_ = config[RECOIL].as<Vector2>();
        if (recoil_.x() < 0 or recoil_.y() < 0)
            throw BadConfigFile(RECOIL_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(COWBOY_PISTOL_RECOIL_ERROR);
    }
}

#define MAGNUM_CONFIG_FILE "config/weapons/magnum.yaml"

#define MAGNUM_AMMO_ERROR PARSING_ERROR_BEGIN " " MAGNUM " " AMMO ". " PARSING_ERROR_END " " U8
#define MAGNUM_REACH_ERROR PARSING_ERROR_BEGIN " " MAGNUM " " REACH ". " PARSING_ERROR_END " " FLOAT
#define MAGNUM_DISPERSION_ERROR \
    PARSING_ERROR_BEGIN " " MAGNUM " " DISPERSION ". " PARSING_ERROR_END " " FLOAT
#define MAGNUM_RECOIL_ERROR \
    PARSING_ERROR_BEGIN " " MAGNUM " " RECOIL ". " PARSING_ERROR_END " " FLOAT

void Config::Weapons::Magnum::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + MAGNUM_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + MAGNUM_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + MAGNUM_CONFIG_FILE + NOT_VALID);
    }

    try {
        const int _ammo = config[AMMO].as<int>();
        if (_ammo < std::numeric_limits<u8>::min() or _ammo > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        ammo_ = _ammo;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(MAGNUM_AMMO_ERROR);
    }

    try {
        reach_ = config[REACH].as<float>();
        if (reach_ < 0)
            throw BadConfigFile(REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(MAGNUM_REACH_ERROR);
    }

    try {
        dispersion_ = config[DISPERSION].as<float>();
        if (dispersion_ < 0)
            throw BadConfigFile(DISPERSION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(MAGNUM_DISPERSION_ERROR);
    }

    try {
        recoil_ = config[RECOIL].as<Vector2>();
        if (recoil_.x() < 0 or recoil_.y() < 0)
            throw BadConfigFile(RECOIL_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(MAGNUM_RECOIL_ERROR);
    }
}

#define PELLETS_PER_SHOT "pellets per shot"
#define RELOAD_TIME "reload time"

#define SHOTGUN_CONFIG_FILE "config/weapons/shotgun.yaml"

#define SHOTGUN_AMMO_ERROR PARSING_ERROR_BEGIN " " SHOTGUN " " AMMO ". " PARSING_ERROR_END " " U8
#define SHOTGUN_REACH_ERROR \
    PARSING_ERROR_BEGIN " " SHOTGUN " " REACH ". " PARSING_ERROR_END " " FLOAT
#define SHOTGUN_DISPERSION_ERROR \
    PARSING_ERROR_BEGIN " " SHOTGUN " " DISPERSION ". " PARSING_ERROR_END " " FLOAT
#define SHOTGUN_RECOIL_ERROR \
    PARSING_ERROR_BEGIN " " SHOTGUN " " RECOIL ". " PARSING_ERROR_END " " FLOAT
#define PELLETS_PER_SHOT_ERROR \
    PARSING_ERROR_BEGIN " " SHOTGUN " " PELLETS_PER_SHOT ". " PARSING_ERROR_END " " U8
#define RELOAD_TIME_ERROR \
    PARSING_ERROR_BEGIN " " SHOTGUN " " RELOAD_TIME ". " PARSING_ERROR_END " " FLOAT

#define RELOAD_TIME_BAD_VALUE "Reload time must be greater or equal than 0"

void Config::Weapons::Shotgun::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + SHOTGUN_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + SHOTGUN_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + SHOTGUN_CONFIG_FILE + NOT_VALID);
    }

    try {
        const int _ammo = config[AMMO].as<int>();
        if (_ammo < std::numeric_limits<u8>::min() or _ammo > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        ammo_ = _ammo;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(SHOTGUN_AMMO_ERROR);
    }

    try {
        dispersion_ = config[DISPERSION].as<float>();
        if (dispersion_ < 0)
            throw BadConfigFile(DISPERSION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(SHOTGUN_DISPERSION_ERROR);
    }

    try {
        recoil_ = config[RECOIL].as<Vector2>();
        if (recoil_.x() < 0 or recoil_.y() < 0)
            throw BadConfigFile(RECOIL_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(SHOTGUN_RECOIL_ERROR);
    }

    try {
        minReach_ = config[MIN_REACH].as<float>();
        if (minReach_ < 0)
            throw BadConfigFile(REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(SHOTGUN_REACH_ERROR);
    }

    try {
        maxReach_ = config[MAX_REACH].as<float>();
        if (maxReach_ < 0)
            throw BadConfigFile(REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(SHOTGUN_REACH_ERROR);
    }

    try {
        pelletsPerShot_ = config[PELLETS_PER_SHOT].as<int>();
        if (pelletsPerShot_ < std::numeric_limits<u8>::min() or
            pelletsPerShot_ > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(PELLETS_PER_SHOT_ERROR);
    }

    try {
        reloadTime_ = config[RELOAD_TIME].as<float>();
        if (reloadTime_ < 0)
            throw BadConfigFile(RELOAD_TIME_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(RELOAD_TIME_ERROR);
    }
}

#define SNIPER_CONFIG_FILE "config/weapons/sniper.yaml"

#define SNIPER_AMMO_ERROR PARSING_ERROR_BEGIN " " SNIPER " " AMMO ". " PARSING_ERROR_END " " U8
#define SNIPER_REACH_ERROR PARSING_ERROR_BEGIN " " SNIPER " " REACH ". " PARSING_ERROR_END " " FLOAT
#define SNIPER_DISPERSION_ERROR \
    PARSING_ERROR_BEGIN " " SNIPER " " DISPERSION ". " PARSING_ERROR_END " " FLOAT
#define SNIPER_RECOIL_ERROR \
    PARSING_ERROR_BEGIN " " SNIPER " " RECOIL ". " PARSING_ERROR_END " " FLOAT
#define SNIPER_RELOAD_TIME_ERROR \
    PARSING_ERROR_BEGIN " " SNIPER " " RELOAD_TIME ". " PARSING_ERROR_END " " FLOAT

void Config::Weapons::Sniper::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + SNIPER_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + SNIPER_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + SNIPER_CONFIG_FILE + NOT_VALID);
    }

    try {
        const int _ammo = config[AMMO].as<int>();
        if (_ammo < std::numeric_limits<u8>::min() or _ammo > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        ammo_ = _ammo;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(SNIPER_AMMO_ERROR);
    }

    try {
        reach_ = config[REACH].as<float>();
        if (reach_ < 0)
            throw BadConfigFile(REACH_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(SNIPER_REACH_ERROR);
    }

    try {
        dispersion_ = config[DISPERSION].as<float>();
        if (dispersion_ < 0)
            throw BadConfigFile(DISPERSION_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(SNIPER_DISPERSION_ERROR);
    }

    try {
        recoil_ = config[RECOIL].as<Vector2>();
        if (recoil_.x() < 0 or recoil_.y() < 0)
            throw BadConfigFile(RECOIL_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(SNIPER_RECOIL_ERROR);
    }

    try {
        reloadTime_ = config[RELOAD_TIME].as<float>();
        if (reloadTime_ < 0)
            throw BadConfigFile(RELOAD_TIME_BAD_VALUE);
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(SNIPER_RELOAD_TIME_ERROR);
    }
}

#define ARMOR_CONFIG_FILE "config/armor.yaml"

#define ARMOR_ERROR PARSING_ERROR_BEGIN " " ARMOR ". " PARSING_ERROR_END " " U8
#define HELMET_ERROR PARSING_ERROR_BEGIN " " HELMET ". " PARSING_ERROR_END " " U8

#define ARMOR_BAD_VALUE "Armor must be greater or equal than 0"
#define HELMET_BAD_VALUE "Helmet must be greater or equal than 0"

void Config::Armor::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + ARMOR_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + ARMOR_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + ARMOR_CONFIG_FILE + NOT_VALID);
    }

    try {
        const int _armor = config[ARMOR].as<int>();
        if (_armor < 0)
            throw BadConfigFile(ARMOR_BAD_VALUE);
        armor_ = _armor;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(ARMOR_ERROR);
    }

    try {
        const int _helmet = config[HELMET].as<int>();
        if (_helmet < 0)
            throw BadConfigFile(HELMET_BAD_VALUE);
        helmet_ = _helmet;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(HELMET_ERROR);
    }
}

#define MATCH "match"

#define MATCH_CONFIG_FILE "config/match.yaml"

#define ROUNDS "rounds"
#define POINTS_TO_WIN "points to win"

#define ROUNDS_ERROR PARSING_ERROR_BEGIN " " ROUNDS ". " PARSING_ERROR_END " " U8
#define POINTS_TO_WIN_ERROR PARSING_ERROR_BEGIN " " POINTS_TO_WIN ". " PARSING_ERROR_END " " U8

void Config::Match::load() {
    using YAML::Node, YAML::LoadFile, YAML::ParserException, YAML::BadFile;

    Node config;

    try {
        config = LoadFile(configDirectory + MATCH_CONFIG_FILE);
    } catch (const BadFile& _) {
        throw BadConfigFile(COULD_NOT_OPEN_FILE + configDirectory + MATCH_CONFIG_FILE);
    } catch (const ParserException& _) {
        throw BadConfigFile(CONFIG_FILE_AT + configDirectory + MATCH_CONFIG_FILE + NOT_VALID);
    }

    try {
        const int _rounds = config[ROUNDS].as<int>();
        if (_rounds < std::numeric_limits<u8>::min() or _rounds > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        rounds_ = _rounds;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(ROUNDS_ERROR);
    }

    try {
        const int _pointsToWin = config[POINTS_TO_WIN].as<int>();
        if (_pointsToWin < std::numeric_limits<u8>::min() or
            _pointsToWin > std::numeric_limits<u8>::max())
            throw YAML::TypedBadConversion<u8>(YAML::Mark::null_mark());
        pointsToWin_ = _pointsToWin;
    } catch (const YAML::BadConversion& _) {
        throw BadConfigFile(POINTS_TO_WIN_ERROR);
    }
}

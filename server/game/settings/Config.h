#pragma once

#include <string>

#include <yaml-cpp/yaml.h>

#include "ItemID.h"
#include "Vector2.h"

/**
 * The global configuration of the game
 */
class Config {
    static const HashMap<std::string, ItemID> itemIDs;
    static const HashMap<ItemID, u8>& getDefaultAmmoMap();
    static std::string configDirectory;
    static std::string mapsDirectory_;

public:
    static u8 getDefaultAmmo(ItemID id);
    struct BadConfigFile final: std::runtime_error {
        explicit BadConfigFile(const std::string& message);
    };

    Config() = delete;
    Config(const Config& other) = delete;
    Config(Config&& other) noexcept = delete;
    Config& operator=(const Config& other) = delete;
    Config& operator=(Config&& other) noexcept = delete;
    ~Config() = default;

    /**
     * Set the path to the configuration file
     * @param path The path to the configuration file
     */
    static void setConfigPath(std::string path);

    /**
     * Set the path to the maps directory
     * @param maps The path to the maps directory
     */
    static void setMapsDirectory(std::string maps);

    /**
     * Load the configuration of the game
     */
    static const std::string& mapsDirectory();

    /**
     * Load the configuration from the configuration file
     */
    static void load();

    class Duck {
        static float jumpTime_;
        static float acceleration_;
        static float airAcceleration_;
        static float minSpeed_;
        static float maxSpeed_;
        static float jumpSpeed_;
        static ItemID defaultWeapon_;
        static bool defaultArmor_;
        static bool defaultHelmet_;

        /**
         * Load the configuration of the duck from the duck configuration file
         */
        static void load();

        friend class Config;

    public:
        Duck() = delete;
        Duck(const Duck& other) = delete;
        Duck(Duck&& other) noexcept = delete;
        Duck& operator=(const Duck& other) = delete;
        Duck& operator=(Duck&& other) noexcept = delete;
        ~Duck() = delete;

        static float jumpTime();
        static float acceleration();
        static float airAcceleration();
        static float minSpeed();
        static float maxSpeed();
        static float jumpSpeed();
        static ItemID defaultWeapon();
        static bool defaultArmor();
        static bool defaultHelmet();
    };

    class Physics {
        static float gravity_;

        /**
         * Load the configuration of the physics from the physics configuration file
         */
        static void load();

        friend class Config;

    public:
        Physics() = delete;
        Physics(const Physics& other) = delete;
        Physics(Physics&& other) noexcept = delete;
        Physics& operator=(const Physics& other) = delete;
        Physics& operator=(Physics&& other) noexcept = delete;

        static float gravity();
    };

    class Weapons {
        static float minSpawnTime_;
        static float maxSpawnTime_;

        /**
         * Load the configuration of the weapons from the weapons configuration file
         */
        static void load();

        friend class Config;

    public:
        Weapons() = delete;
        Weapons(const Weapons& other) = delete;
        Weapons(Weapons&& other) noexcept = delete;
        Weapons& operator=(const Weapons& other) = delete;
        Weapons& operator=(Weapons&& other) noexcept = delete;

        static float minSpawnTime();
        static float maxSpawnTime();

        class Grenade {
            static u8 ammo_;
            static float reach_;
            static float radius_;
            static float explosionTime_;

            /**
             * Load the configuration of the grenade from the grenade configuration file
             */
            static void load();

            friend class Config;

        public:
            Grenade() = delete;
            Grenade(const Grenade& other) = delete;
            Grenade(Grenade&& other) noexcept = delete;
            Grenade& operator=(const Grenade& other) = delete;
            Grenade& operator=(Grenade&& other) noexcept = delete;
            ~Grenade() = delete;

            static u8 ammo();
            static float reach();
            static float radius();
            static float explosionTime();
        };

        class Banana {
            static u8 ammo_;
            static float reach_;

            /**
             * Load the configuration of the banana from the banana configuration file
             */
            static void load();

            friend class Config;

        public:
            Banana() = delete;
            Banana(const Banana& other) = delete;
            Banana(Banana&& other) noexcept = delete;
            Banana& operator=(const Banana& other) = delete;
            Banana& operator=(Banana&& other) noexcept = delete;
            ~Banana() = delete;

            static u8 ammo();
            static float reach();
        };

        class PewPewLaser {
            static u8 ammo_;
            static float dispersion_;
            static Vector2 recoil_;
            static float minReach_;
            static float maxReach_;
            static u8 raysPerShot_;

            /**
             * Load the configuration of the pew pew laser from the pew pew laser configuration file
             */
            static void load();

            friend class Config;

        public:
            PewPewLaser() = delete;
            PewPewLaser(const PewPewLaser& other) = delete;
            PewPewLaser(PewPewLaser&& other) noexcept = delete;
            PewPewLaser& operator=(const PewPewLaser& other) = delete;
            PewPewLaser& operator=(PewPewLaser&& other) noexcept = delete;
            ~PewPewLaser() = delete;

            static u8 ammo();
            static float dispersion();
            static Vector2 recoil();
            static float minReach();
            static float maxReach();
            static u8 raysPerShot();
        };

        class LaserRifle {
            static u8 ammo_;
            static float reach_;
            static float dispersion_;
            static Vector2 recoil_;
            static float timeBetweenShots_;
            static float rayAngle_;
            static u8 bounces_;

            /**
             * Load the configuration of the laser rifle from the laser rifle configuration file
             */
            static void load();

            friend class Config;

        public:
            LaserRifle() = delete;
            LaserRifle(const LaserRifle& other) = delete;
            LaserRifle(LaserRifle&& other) noexcept = delete;
            LaserRifle& operator=(const LaserRifle& other) = delete;
            LaserRifle& operator=(LaserRifle&& other) noexcept = delete;
            ~LaserRifle() = delete;

            static u8 ammo();
            static float reach();
            static float dispersion();
            static Vector2 recoil();
            static float timeBetweenShots();
            static float rayAngle();
            static u8 bounces();
        };

        class Ak47 {
            static u8 ammo_;
            static float reach_;
            static Vector2 recoil_;
            static float timeBetweenShots_;
            static float minDispersion_;
            static float midDispersion_;
            static float maxDispersion_;

            /**
             * Load the configuration of the ak47 from the ak47 configuration file
             */
            static void load();

            friend class Config;

        public:
            Ak47() = delete;
            Ak47(const Ak47& other) = delete;
            Ak47(Ak47&& other) noexcept = delete;
            Ak47& operator=(const Ak47& other) = delete;
            Ak47& operator=(Ak47&& other) noexcept = delete;
            ~Ak47() = delete;

            static u8 ammo();
            static float reach();
            static Vector2 recoil();
            static float timeBetweenShots();
            static float minDispersion();
            static float midDispersion();
            static float maxDispersion();
        };

        class DuelPistol {
            static u8 ammo_;
            static float reach_;
            static float dispersion_;
            static Vector2 recoil_;

            /**
             * Load the configuration of the duel pistol from the duel pistol configuration file
             */
            static void load();

            friend class Config;

        public:
            DuelPistol() = delete;
            DuelPistol(const DuelPistol& other) = delete;
            DuelPistol(DuelPistol&& other) noexcept = delete;
            DuelPistol& operator=(const DuelPistol& other) = delete;
            DuelPistol& operator=(DuelPistol&& other) noexcept = delete;
            ~DuelPistol() = delete;

            static u8 ammo();
            static float reach();
            static float dispersion();
            static Vector2 recoil();
        };

        class CowboyPistol {
            static u8 ammo_;
            static float reach_;
            static float dispersion_;
            static Vector2 recoil_;

            /**
             * Load the configuration of the cowboy pistol from the cowboy pistol configuration file
             */
            static void load();

            friend class Config;

        public:
            CowboyPistol() = delete;
            CowboyPistol(const CowboyPistol& other) = delete;
            CowboyPistol(CowboyPistol&& other) noexcept = delete;
            CowboyPistol& operator=(const CowboyPistol& other) = delete;
            CowboyPistol& operator=(CowboyPistol&& other) noexcept = delete;
            ~CowboyPistol() = delete;

            static u8 ammo();
            static float reach();
            static float dispersion();
            static Vector2 recoil();
        };

        class Magnum {
            static u8 ammo_;
            static float reach_;
            static float dispersion_;
            static Vector2 recoil_;

            /**
             * Load the configuration of the magnum from the magnum configuration file
             */
            static void load();

            friend class Config;

        public:
            Magnum() = delete;
            Magnum(const Magnum& other) = delete;
            Magnum(Magnum&& other) noexcept = delete;
            Magnum& operator=(const Magnum& other) = delete;
            Magnum& operator=(Magnum&& other) noexcept = delete;
            ~Magnum() = delete;

            static u8 ammo();
            static float reach();
            static float dispersion();
            static Vector2 recoil();
        };

        class Shotgun {
            static u8 ammo_;
            static float dispersion_;
            static Vector2 recoil_;
            static float minReach_;
            static float maxReach_;
            static u8 pelletsPerShot_;
            static float reloadTime_;

            /**
             * Load the configuration of the shotgun from the shotgun configuration file
             */
            static void load();

            friend class Config;

        public:
            Shotgun() = delete;
            Shotgun(const Shotgun& other) = delete;
            Shotgun(Shotgun&& other) noexcept = delete;
            Shotgun& operator=(const Shotgun& other) = delete;
            Shotgun& operator=(Shotgun&& other) noexcept = delete;
            ~Shotgun() = delete;

            static u8 ammo();
            static float dispersion();
            static Vector2 recoil();
            static float minReach();
            static float maxReach();
            static u8 pelletsPerShot();
            static float reloadTime();
        };

        class Sniper {
            static u8 ammo_;
            static float reach_;
            static float dispersion_;
            static Vector2 recoil_;
            static float reloadTime_;

            /**
             * Load the configuration of the sniper from the sniper configuration file
             */
            static void load();

            friend class Config;

        public:
            Sniper() = delete;
            Sniper(const Sniper& other) = delete;
            Sniper(Sniper&& other) noexcept = delete;
            Sniper& operator=(const Sniper& other) = delete;
            Sniper& operator=(Sniper&& other) noexcept = delete;
            ~Sniper() = delete;

            static u8 ammo();
            static float reach();
            static float dispersion();
            static Vector2 recoil();
            static float reloadTime();
        };
    };

    class Armor {
        static u8 armor_;
        static u8 helmet_;

        /**
         * Load the configuration of the armor from the armor configuration file00
         */
        static void load();

        friend class Config;

    public:
        Armor() = delete;
        Armor(const Armor& other) = delete;
        Armor(Armor&& other) noexcept = delete;
        Armor& operator=(const Armor& other) = delete;
        Armor& operator=(Armor&& other) noexcept = delete;
        ~Armor() = delete;

        static u8 armor();
        static u8 helmet();
    };

    class Match {
        static u8 rounds_;
        static u8 pointsToWin_;

        /**
         * Load the configuration of the match from the match configuration file
         */
        static void load();

        friend class Config;

    public:
        Match() = delete;
        Match(const Match& other) = delete;
        Match(Match&& other) noexcept = delete;
        Match& operator=(const Match& other) = delete;
        Match& operator=(Match&& other) noexcept = delete;
        ~Match() = delete;

        static u8 rounds();
        static u8 pointsToWin();
    };
};

inline float Config::Duck::jumpTime() { return jumpTime_; }
inline float Config::Duck::acceleration() { return acceleration_; }
inline float Config::Duck::airAcceleration() { return airAcceleration_; }
inline float Config::Duck::minSpeed() { return minSpeed_; }
inline float Config::Duck::maxSpeed() { return maxSpeed_; }
inline float Config::Duck::jumpSpeed() { return jumpSpeed_; }
inline ItemID Config::Duck::defaultWeapon() { return defaultWeapon_; }
inline bool Config::Duck::defaultArmor() { return defaultArmor_; }
inline bool Config::Duck::defaultHelmet() { return defaultHelmet_; }
inline float Config::Physics::gravity() { return gravity_; }
inline float Config::Weapons::minSpawnTime() { return minSpawnTime_; }
inline float Config::Weapons::maxSpawnTime() { return maxSpawnTime_; }
inline u8 Config::Weapons::Grenade::ammo() { return ammo_; }
inline float Config::Weapons::Grenade::reach() { return reach_; }
inline float Config::Weapons::Grenade::radius() { return radius_; }
inline float Config::Weapons::Grenade::explosionTime() { return explosionTime_; }
inline u8 Config::Weapons::Banana::ammo() { return ammo_; }
inline float Config::Weapons::Banana::reach() { return reach_; }
inline u8 Config::Weapons::PewPewLaser::ammo() { return ammo_; }
inline float Config::Weapons::PewPewLaser::dispersion() { return dispersion_; }
inline Vector2 Config::Weapons::PewPewLaser::recoil() { return recoil_; }
inline float Config::Weapons::PewPewLaser::minReach() { return minReach_; }
inline float Config::Weapons::PewPewLaser::maxReach() { return maxReach_; }
inline u8 Config::Weapons::PewPewLaser::raysPerShot() { return raysPerShot_; }
inline u8 Config::Weapons::LaserRifle::ammo() { return ammo_; }
inline float Config::Weapons::LaserRifle::reach() { return reach_; }
inline float Config::Weapons::LaserRifle::dispersion() { return dispersion_; }
inline Vector2 Config::Weapons::LaserRifle::recoil() { return recoil_; }
inline float Config::Weapons::LaserRifle::timeBetweenShots() { return timeBetweenShots_; }
inline float Config::Weapons::LaserRifle::rayAngle() { return rayAngle_; }
inline u8 Config::Weapons::LaserRifle::bounces() { return bounces_; }
inline u8 Config::Weapons::Ak47::ammo() { return ammo_; }
inline float Config::Weapons::Ak47::reach() { return reach_; }
inline Vector2 Config::Weapons::Ak47::recoil() { return recoil_; }
inline float Config::Weapons::Ak47::timeBetweenShots() { return timeBetweenShots_; }
inline float Config::Weapons::Ak47::minDispersion() { return minDispersion_; }
inline float Config::Weapons::Ak47::midDispersion() { return midDispersion_; }
inline float Config::Weapons::Ak47::maxDispersion() { return maxDispersion_; }
inline u8 Config::Weapons::DuelPistol::ammo() { return ammo_; }
inline float Config::Weapons::DuelPistol::reach() { return reach_; }
inline float Config::Weapons::DuelPistol::dispersion() { return dispersion_; }
inline Vector2 Config::Weapons::DuelPistol::recoil() { return recoil_; }
inline u8 Config::Weapons::CowboyPistol::ammo() { return ammo_; }
inline float Config::Weapons::CowboyPistol::reach() { return reach_; }
inline float Config::Weapons::CowboyPistol::dispersion() { return dispersion_; }
inline Vector2 Config::Weapons::CowboyPistol::recoil() { return recoil_; }
inline u8 Config::Weapons::Magnum::ammo() { return ammo_; }
inline float Config::Weapons::Magnum::reach() { return reach_; }
inline float Config::Weapons::Magnum::dispersion() { return dispersion_; }
inline Vector2 Config::Weapons::Magnum::recoil() { return recoil_; }
inline u8 Config::Weapons::Shotgun::ammo() { return ammo_; }
inline float Config::Weapons::Shotgun::dispersion() { return dispersion_; }
inline Vector2 Config::Weapons::Shotgun::recoil() { return recoil_; }
inline float Config::Weapons::Shotgun::minReach() { return minReach_; }
inline float Config::Weapons::Shotgun::maxReach() { return maxReach_; }
inline u8 Config::Weapons::Shotgun::pelletsPerShot() { return pelletsPerShot_; }
inline float Config::Weapons::Shotgun::reloadTime() { return reloadTime_; }
inline u8 Config::Weapons::Sniper::ammo() { return ammo_; }
inline float Config::Weapons::Sniper::reach() { return reach_; }
inline float Config::Weapons::Sniper::dispersion() { return dispersion_; }
inline Vector2 Config::Weapons::Sniper::recoil() { return recoil_; }
inline float Config::Weapons::Sniper::reloadTime() { return reloadTime_; }
inline u8 Config::Armor::armor() { return armor_; }
inline u8 Config::Armor::helmet() { return helmet_; }
inline u8 Config::Match::rounds() { return rounds_; }
inline u8 Config::Match::pointsToWin() { return pointsToWin_; }

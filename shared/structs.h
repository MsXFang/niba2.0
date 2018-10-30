#pragma once
#include <array>
#include <nlohmann/json.hpp>

namespace nibashared {

struct battlestats {
    int attack_min{0};
    int attack_max{0};
    int accuracy{0};
    int evasion{0};
    int speed{0};
    int hp{0};
    int mp{0};
    int inner_power{0};
    int defence{0};

    // this is inlined
    battlestats &operator+=(const battlestats &rhs) {
        attack_min += rhs.attack_min;
        attack_max += rhs.attack_max;
        accuracy += rhs.accuracy;
        evasion += rhs.evasion;
        speed += rhs.speed;
        hp += rhs.hp;
        mp += rhs.mp;
        inner_power += rhs.inner_power;
        defence += rhs.defence;
        return *this;
    }
};
void to_json(nlohmann::json &j, const battlestats &stats);
void from_json(const nlohmann::json &j, battlestats &stats);

constexpr std::size_t MAX_ACTIVE_MAGIC = 5;

using character_magic_ids = std::array<int, MAX_ACTIVE_MAGIC>;

struct attributes {
    int strength;
    int dexterity;
    int physique;
    int spirit;
};
void to_json(nlohmann::json &j, const attributes &attr);
void from_json(const nlohmann::json &j, attributes &attr);

// a character
struct character {
    std::string name;
    int id; // definitely unique

    // attributes
    attributes attrs;

    // we don't really need this in our database
    battlestats stats;

    // since we will be passing this around
    // it's probably a better idea to use ids
    character_magic_ids active_magic;

    // add something like from_db_json, or compose something
    // to make it work better
    // TODO equipments
};
void to_json(nlohmann::json &j, const character &character);
void from_json(const nlohmann::json &j, character &character);

struct magic {
    std::string name;
    int id;

    int active; // has CD?
    int cd;
    int multiplier;   // in percentage
    int inner_damage; // certain value

    battlestats stats;
};
void to_json(nlohmann::json &j, const magic &magic);
void from_json(const nlohmann::json &j, magic &magic);

const static magic DEFAULT_MAGIC{u8"default", 0, 1, 0, 100, 100, {}};

}; // namespace nibashared

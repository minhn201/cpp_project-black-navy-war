#ifndef UNIT_HPP
#define UNIT_HPP

#include <string>
#include <vector>
#include "logics/naval_base.hpp"
#include "graphics/renderer.hpp"

class Unit
{
public:
    Unit(std::string type, bool is_player_unit);
    ~Unit();

    void attack(Unit &other);
    void attack(NavalBase &other);
    void take_damage(float damage);
    void move(float direction);
    bool is_destroyed();
    float get_position();
    std::string get_type();
    float get_speed();
    std::vector<float> get_window_position(RenderWindow &render_window);
    bool shouldOccur(float probability);

private:
    float pos_;                // This is just an int in the range 0 to 100
    float health_;             // Most likely an int to represent the ships health
    float damage_;             // Most likely an into to represent how much damage the ship does
    float speed_;              // A floating point to represent the speed of the ship
    std::string type_;         // This could be a string or an enum type that contains the names of all ships
    std::vector<float> shape_; // This could be a set of vertices that make up the ships bounding box
    bool is_destroyed_;
};

#endif
#ifndef GAME_HPP
#define GAME_HPP

#include "logics/Unit.hpp"
#include "logics/resources.hpp"
#include "logics/naval_base.hpp"
#include <vector>
#include <string>

class Game {
    private:
        NavalBase friendly_base_;
        NavalBase enemy_base_;
        Resources resources_;
        std::vector<Unit> friendly_units_;
        std::vector<Unit> enemy_units_;
        float income_upgrade_cost_;
        float health_regen_upgrade_cost_;
        float max_health_upgrade_cost_;
        float max_resources_upgrade_cost_;


    public:
        // default constructor
        Game();

        // Allows the user to purchase a specific unit
        void purchase_unit(std::string type);

        // Plays the next turn of the loop meaning:
        // Income is generated
        // Health is regenerated
        // Units move forward
        // Units attack if they are sufficiently close
        void play_turn();

        // Allows the user to purchase the max health upgrade if they have sufficient resources
        void purchase_max_health_upgrade();

        // Allows the user to purchase the health regen upgrade if they have sufficient resources
        void purchase_health_regen_upgrade();

        // Allows the user to purchase the max resources upgrade if they have sufficient resources
        void purhcase_max_resource_upgrade();

        // Allows the user to purchase the income upgrade if they have sufficient resources
        void purchase_income_upgrade();


};

#endif

/*
Keeps track of the friendly units, enemy units as well as the friendly and enemy bases. Also keeps track of resources and costs
for units and upgrades


upgrades include:
- increasing the amount of resources gained
- increasing the amount of health gained per second
- increasing bases max health
- Increasing maximum amount of resources allowed

Game class

data members:
- List of all friendly units
- List of all enemy units
- Friendly base
- Enemy base
- Resources
- Upgrades and costs

*/
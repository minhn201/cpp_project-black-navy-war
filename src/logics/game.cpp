#include "logics/game.hpp"

// Specify the cost of different units
const float patrol_cost = 70.0f;
const float destroyer_cost = 200.0f;
const float submarine_cost = 120.0f;
const float bomber_cost = 160.0f;
const float helicopter_cost = 260.0f;


// Set max upgrade cost to avoid infinite upgrading
const float max_upgrade_cost = 3200.0f;


// default game constructor
Game::Game() {
    // All upgrades start at 200 cost
    income_upgrade_cost_ = 200.0f;
    health_regen_upgrade_cost_ = 200.0f;
    max_health_upgrade_cost_ = 200.0f;
    max_resources_upgrade_cost_ = 200.0f;

    // Additional data members are default constructed upon declaration
}


// Allows the user to purchase a specific unit
void Game::purchase_unit(std::string type) {
    if (type == "Patrol Boat") {
        if (resources_.get_resources() >= patrol_cost) { // Ensure the player has sufficient resources
            friendly_units_.emplace_back(type, true); // add a patrol boat unit to the vector of friendly units
            resources_.purchase(patrol_cost); // Pay the amount of a patrol boat
        }

    } else if (type == "Destroyer") {
        if (resources_.get_resources() >= destroyer_cost) { // Ensure the player has sufficient resources
            friendly_units_.emplace_back(type, true); // add a destroyer unit to the friendly units
            resources.purchase(destroyer_cost); // Pay the amount of a destroyer
        }

    } else if (type == "Submarine") {
        if (resources_.get_resources() >= submarine_cost) { // Ensure the player has sufficient resources
            friendly_units_.emplace_back(type, true); // add a submarine unit to the friendly units
            resources.purchase(submarine_cost); // Pay the amount of a submarine
        }

    } else if (type == "Bomber") {
        if (resources_.get_resources() >= bomber_cost) { // Ensure the player has sufficient resources
            friendly_units_.emplace_back(type, true); // add a bomber unit to the friendly units
            resources.purchase(bomber_cost); // Pay the amount of a bomber
        }

    } else if (type == "Helicopter") {
        if (resources_.get_resources() >= helicopter_cost) { // Ensure the player has sufficient resources
            friendly_units_.emplace_back(type, true); // add a helicopter unit to the friendly units
            resources.purchase(helicopter_cost); // Pay the amount of a helicopter
        }
    }
}

// Plays the next turn of the loop meaning:
// Income is generated
// Health is regenerated
// Units move forward
// Units attack if they are sufficiently close
void Game::play_turn();

// Allows the user to purchase the max health upgrade if they have sufficient resources
void Game::purchase_max_health_upgrade() {
    if (max_health_upgrade_cost_ > max_upgrade_cost) { // If max upgrade has happened don't allow additional upgrades
        return;
    }

    if (resources_.get_resources() >= max_health_upgrade_cost_) {
        friendly_base_.upgrade_health(); // Apply the upgrade
        resources_.purchase(max_health_upgrade_cost_); // Pay for the upgrade
        max_health_upgrade_cost_ *= 2; // Increase the cost
    }
 }

// Allows the user to purchase the health regen upgrade if they have sufficient resources
void Game::purchase_health_regen_upgrade() {
    if (health_regen_upgrade_cost_ > max_upgrade_cost) { // If max upgrade has happened don't allow additional upgrades
        return;
    }
    
    if (resources_.get_resources() >= health_regen_upgrade_cost_) {
        friendly_base_.upgrade_regeneration(); // Apply the upgrade
        resources_.purchase(health_regen_upgrade_cost_); // Pay for the upgrade
        health_regen_upgrade_cost_ *= 2; // Increase the cost
    }
}

// Allows the user to purchase the max resources upgrade if they have sufficient resources
void Game::purhcase_max_resource_upgrade() {
    if (max_resources_upgrade_cost_ > max_upgrade_cost) { // If max upgrade has happened don't allow additional upgrades
        return;
    }
    
    if (resources_.get_resources() >= max_resources_upgrade_cost_) {
        resources_.upgrade_max_resources(); // Apply the upgrade
        resources_.purchase(max_resources_upgrade_cost_); // Pay for the upgrade
        max_resources_upgrade_cost_ *= 2; // Increase the cost
    }
}

// Allows the user to purchase the income upgrade if they have sufficient resources
void Game::purchase_income_upgrade() {
    if (income_upgrade_cost_ > max_upgrade_cost) { // If max upgrade has happened don't allow additional upgrades
        return;
    }
    
    if (resources_.get_resources() >= income_upgrade_cost_) {
        resources_.upgrade_income(); // Apply the upgrade
        resources_.purchase(income_upgrade_cost_); // Pay for the upgrade
        income_upgrade_cost_ *= 2; // Increase the cost
    }
}

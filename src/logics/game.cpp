#include "logics/game.hpp"
#include <iostream>

// Specify the cost of different units
const float patrol_cost = 70.0f;
const float destroyer_cost = 200.0f;
const float submarine_cost = 120.0f;
const float bomber_cost = 160.0f;
const float helicopter_cost = 260.0f;

// Set max upgrade cost to avoid infinite upgrading
const float max_upgrade_cost = 800.0f;

// Set unit range
const float unit_range = 5.0f;

// default game constructor
Game::Game()
{
    // All upgrades start at 200 cost
    income_upgrade_cost_ = 200.0f;
    health_regen_upgrade_cost_ = 200.0f;
    max_health_upgrade_cost_ = 200.0f;
    max_resources_upgrade_cost_ = 200.0f;

    std::srand(std::time(0)); // Initialize seed for random enemy unit creation
    // Additional data members are default constructed upon declaration
}

// Allows the user to purchase a specific unit
void Game::purchase_unit(std::string type)
{
    if (type == "Patrol Boat")
    {
        if (resources_.get_resources() >= patrol_cost)
        {                                             // Ensure the player has sufficient resources
            friendly_units_.emplace_back(type, true); // add a patrol boat unit to the vector of friendly units
            resources_.purchase(patrol_cost);         // Pay the amount of a patrol boat
        }
    }
    else if (type == "Destroyer")
    {
        if (resources_.get_resources() >= destroyer_cost)
        {                                             // Ensure the player has sufficient resources
            friendly_units_.emplace_back(type, true); // add a destroyer unit to the friendly units
            resources_.purchase(destroyer_cost);      // Pay the amount of a destroyer
        }
    }
    else if (type == "Submarine")
    {
        if (resources_.get_resources() >= submarine_cost)
        {                                             // Ensure the player has sufficient resources
            friendly_units_.emplace_back(type, true); // add a submarine unit to the friendly units
            resources_.purchase(submarine_cost);      // Pay the amount of a submarine
        }
    }
    else if (type == "Bomber")
    {
        if (resources_.get_resources() >= bomber_cost)
        {                                             // Ensure the player has sufficient resources
            friendly_units_.emplace_back(type, true); // add a bomber unit to the friendly units
            resources_.purchase(bomber_cost);         // Pay the amount of a bomber
        }
    }
    else if (type == "Helicopter")
    {
        if (resources_.get_resources() >= helicopter_cost)
        {                                             // Ensure the player has sufficient resources
            friendly_units_.emplace_back(type, true); // add a helicopter unit to the friendly units
            resources_.purchase(helicopter_cost);     // Pay the amount of a helicopter
        }
    }
}

// Plays the next turn of the loop meaning:
// Income is generated
// Health is regenerated
// Units move forward
// Units attack if they are sufficiently close
void Game::play_turn()
{
    resources_.generate_income();
    friendly_base_.regenerate_health();

    // Make moves for friendly units
    for (int i = 0; i < friendly_units_.size(); ++i)
    {
        if (friendly_units_.at(i).get_position() + unit_range >= 100.0f)
        { // If in range of enemy base shoot
            friendly_units_.at(i).attack(enemy_base_);
            if (enemy_base_.is_destroyed())
            { // friendly player wins
                std::cout << "You Win!\n";
                exit(0);
            }
            continue; // Can only attack one thing at a time so we can go to next unit
        }

        bool did_attack = false;
        for (int j = 0; j < enemy_units_.size(); ++j)
        {
            // Check if they are close enough to attack unit or base
            // If they are then check if the type are the same
            // Otherwise move forward
            if (friendly_units_.at(i).get_position() + unit_range >= enemy_units_.at(j).get_position())
            { // In range to attack unit
                // attack based on types
                if (friendly_units_.at(i).get_type() == "Patrol Boat" && enemy_units_.at(j).get_type() != "Submarine")
                { // Patrol can't shoot submarines
                    friendly_units_.at(i).attack(enemy_units_.at(j));
                    did_attack = true;
                    if (enemy_units_.at(j).is_destroyed())
                    { // If the enemy unit is destroyed then delete it
                        enemy_units_.erase(enemy_units_.begin() + j);
                    }
                    break; // Can only attack one ship at a time so we can go to next iteration of outer loop
                }
                else if (friendly_units_.at(i).get_type() == "Destroyer")
                { // Destroyer can attack anything
                    friendly_units_.at(i).attack(enemy_units_.at(j));
                    did_attack = true;
                    if (enemy_units_.at(j).is_destroyed())
                    { // If the enemy unit is destroyed then delete it
                        enemy_units_.erase(enemy_units_.begin() + j);
                    }
                    break; // Can only attack one ship at a time so we can go to next iteration of outer loop
                }
                else if (friendly_units_.at(i).get_type() == "Submarine" && (enemy_units_.at(j).get_type() == "Submarine" || enemy_units_.at(j).get_type() == "Patrol Boat" || enemy_units_.at(j).get_type() == "Destroyer"))
                { // Sumbarine can't attack air units
                    friendly_units_.at(i).attack(enemy_units_.at(j));
                    did_attack = true;
                    if (enemy_units_.at(j).is_destroyed())
                    { // If the enemy unit is destroyed then delete it
                        enemy_units_.erase(enemy_units_.begin() + j);
                    }
                    break; // Can only attack one ship at a time so we can go to next iteration of outer loop
                }
                else if (friendly_units_.at(i).get_type() == "Bomber" && (enemy_units_.at(j).get_type() == "Patrol Boat" || enemy_units_.at(j).get_type() == "Destroyer" || enemy_units_.at(j).get_type() == "Submarine"))
                { // Bomber can only attack ships and submarines
                    friendly_units_.at(i).attack(enemy_units_.at(j));
                    did_attack = true;
                    if (enemy_units_.at(j).is_destroyed())
                    { // If the enemy unit is destroyed then delete it
                        enemy_units_.erase(enemy_units_.begin() + j);
                    }
                    break; // Can only attack one ship at a time so we can go to next iteration of outer loop
                }
                else if (friendly_units_.at(i).get_type() == "Helicopter")
                { // Helicopter can attack all units
                    friendly_units_.at(i).attack(enemy_units_.at(j));
                    did_attack = true;
                    if (enemy_units_.at(j).is_destroyed())
                    { // If the enemy unit is destroyed then delete it
                        enemy_units_.erase(enemy_units_.begin() + j);
                    }
                    break; // Can only attack one ship at a time so we can go to next iteration of outer loop
                }
            }
        }
        if (!did_attack)
        {
            friendly_units_.at(i).move(friendly_units_.at(i).get_speed()); // If can't attack move forward
        }
    }

    // Make moves for enemy units
    for (int i = 0; i < enemy_units_.size(); ++i)
    {
        if (enemy_units_.at(i).get_position() - unit_range <= 0.0f)
        { // If in range of enemy base shoot
            enemy_units_.at(i).attack(friendly_base_);
            if (friendly_base_.is_destroyed())
            { // friendly player wins
                std::cout << " You Lose!\n";
                exit(0);
            }
            continue; // Can only attack one thing at a time so we can go to next unit
        }

        bool did_attack = false;
        for (int j = 0; j < friendly_units_.size(); ++j)
        {
            // Check if they are close enough to attack unit or base
            // If they are then check if the type are the same
            // Otherwise move forward
            if (enemy_units_.at(i).get_position() - unit_range <= friendly_units_.at(j).get_position())
            { // In range to attack unit
                // attack based on types
                if (enemy_units_.at(i).get_type() == "Patrol Boat" && friendly_units_.at(j).get_type() != "Submarine")
                { // Patrol can't shoot submarines
                    enemy_units_.at(i).attack(friendly_units_.at(j));
                    did_attack = true;
                    if (friendly_units_.at(j).is_destroyed())
                    { // If the enemy unit is destroyed then delete it
                        friendly_units_.erase(friendly_units_.begin() + j);
                    }
                    break; // Can only attack one ship at a time so we can go to next iteration of outer loop
                }
                else if (enemy_units_.at(i).get_type() == "Destroyer")
                { // Destroyer can attack anything
                    enemy_units_.at(i).attack(friendly_units_.at(j));
                    did_attack = true;
                    if (friendly_units_.at(j).is_destroyed())
                    { // If the enemy unit is destroyed then delete it
                        friendly_units_.erase(friendly_units_.begin() + j);
                    }
                    break; // Can only attack one ship at a time so we can go to next iteration of outer loop
                }
                else if (enemy_units_.at(i).get_type() == "Submarine" && (friendly_units_.at(j).get_type() == "Submarine" || friendly_units_.at(j).get_type() == "Patrol Boat" || friendly_units_.at(j).get_type() == "Destroyer"))
                { // Sumbarine can't attack air units
                    enemy_units_.at(i).attack(friendly_units_.at(j));
                    did_attack = true;
                    if (friendly_units_.at(j).is_destroyed())
                    { // If the enemy unit is destroyed then delete it
                        friendly_units_.erase(friendly_units_.begin() + j);
                    }
                    break; // Can only attack one ship at a time so we can go to next iteration of outer loop
                }
                else if (enemy_units_.at(i).get_type() == "Bomber" && (friendly_units_.at(j).get_type() == "Patrol Boat" || friendly_units_.at(j).get_type() == "Destroyer" || friendly_units_.at(j).get_type() == "Submarine"))
                { // Bomber can only attack ships and submarines
                    enemy_units_.at(i).attack(friendly_units_.at(j));
                    did_attack = true;
                    if (friendly_units_.at(j).is_destroyed())
                    { // If the enemy unit is destroyed then delete it
                        friendly_units_.erase(friendly_units_.begin() + j);
                    }
                    break; // Can only attack one ship at a time so we can go to next iteration of outer loop
                }
                else if (enemy_units_.at(i).get_type() == "Helicopter")
                { // Helicopter can attack all units
                    enemy_units_.at(i).attack(friendly_units_.at(j));
                    did_attack = true;
                    if (friendly_units_.at(j).is_destroyed())
                    { // If the enemy unit is destroyed then delete it
                        friendly_units_.erase(friendly_units_.begin() + j);
                    }
                    break; // Can only attack one ship at a time so we can go to next iteration of outer loop
                }
            }
        }
        if (!did_attack)
        {
            enemy_units_.at(i).move(-enemy_units_.at(i).get_speed()); // If can't attack move forward
        }
    }
}

// Plays the next turn of the loop for the enemy computer player
// This function will randomly decide to generate a unit of any type
// There is a high chance nothing happens when this function is called
void Game::play_enemy_turn()
{
    if ((std::rand() % 2000) == 0)
    {
        int type = std::rand() % 5;

        if (type == 0)
        { // Patrol boat
            enemy_units_.emplace_back("Patrol Boat", false);
        }
        else if (type == 1)
        { // Destroyer
            enemy_units_.emplace_back("Destroyer", false);
        }
        else if (type == 2)
        { // Submarine
            enemy_units_.emplace_back("Submarine", false);
        }
        else if (type == 3)
        { // Bomber
            enemy_units_.emplace_back("Bomber", false);
        }
        else if (type == 4)
        { // Helicopter
            enemy_units_.emplace_back("Helicopter", false);
        }
    }
}

// Allows the user to purchase the max health upgrade if they have sufficient resources
void Game::purchase_max_health_upgrade()
{
    if (max_health_upgrade_cost_ > max_upgrade_cost)
    { // If max upgrade has happened don't allow additional upgrades
        return;
    }

    if (resources_.get_resources() >= max_health_upgrade_cost_)
    {
        friendly_base_.upgrade_health();               // Apply the upgrade
        resources_.purchase(max_health_upgrade_cost_); // Pay for the upgrade
        max_health_upgrade_cost_ *= 2;                 // Increase the cost
    }
}

// Allows the user to purchase the health regen upgrade if they have sufficient resources
void Game::purchase_health_regen_upgrade()
{
    if (health_regen_upgrade_cost_ > max_upgrade_cost)
    { // If max upgrade has happened don't allow additional upgrades
        return;
    }

    if (resources_.get_resources() >= health_regen_upgrade_cost_)
    {
        friendly_base_.upgrade_regeneration();           // Apply the upgrade
        resources_.purchase(health_regen_upgrade_cost_); // Pay for the upgrade
        health_regen_upgrade_cost_ *= 2;                 // Increase the cost
    }
}

// Allows the user to purchase the max resources upgrade if they have sufficient resources
void Game::purhcase_max_resource_upgrade()
{
    if (max_resources_upgrade_cost_ > max_upgrade_cost)
    { // If max upgrade has happened don't allow additional upgrades
        return;
    }

    if (resources_.get_resources() >= max_resources_upgrade_cost_)
    {
        resources_.upgrade_max_resources();               // Apply the upgrade
        resources_.purchase(max_resources_upgrade_cost_); // Pay for the upgrade
        max_resources_upgrade_cost_ *= 2;                 // Increase the cost
    }
}

// Allows the user to purchase the income upgrade if they have sufficient resources
void Game::purchase_income_upgrade()
{
    if (income_upgrade_cost_ > max_upgrade_cost)
    { // If max upgrade has happened don't allow additional upgrades
        return;
    }

    if (resources_.get_resources() >= income_upgrade_cost_)
    {
        resources_.upgrade_income();               // Apply the upgrade
        resources_.purchase(income_upgrade_cost_); // Pay for the upgrade
        income_upgrade_cost_ *= 2;                 // Increase the cost
    }
}

float Game::get_income_upgrade_cost()
{
    return income_upgrade_cost_;
}

float Game::get_health_regen_upgrade_cost()
{
    return health_regen_upgrade_cost_;
}

float Game::get_max_health_upgrade_cost()
{
    return max_health_upgrade_cost_;
}

float Game::get_max_resources_upgrade_cost()
{
    return max_resources_upgrade_cost_;
}

float Game::get_max_upgrade_cost()
{
    return max_upgrade_cost;
}

// Return the amount of resources available
Resources Game::get_game_resources()
{
    return resources_;
}

// Returns the vector containing friendly units
std::vector<Unit> Game::get_friendly_units()
{
    return friendly_units_;
}

// Returns the vector containing enemy units
std::vector<Unit> Game::get_enemy_units()
{
    return enemy_units_;
}

NavalBase Game::get_friendly_base()
{
    return friendly_base_;
}

NavalBase Game::get_enemy_base()
{
    return enemy_base_;
}
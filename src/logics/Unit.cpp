#include "logics/Unit.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

const std::string type_patrol = "Patrol Boat";
const std::string type_destroyer = "Destroyer";
const std::string type_submarine = "Submarine";
const std::string type_bomber = "Bomber";
const std::string type_helicopter = "Helicopter";

const float health_patrol = 100.0f;
const float health_destroyer = 300.0f;
const float health_submarine = 150.0f;
const float health_bomber = 60.0f;
const float health_helicopter = 30.0f;

const float speed_patrol = 0.01f;
const float speed_destroyer = 0.004f;
const float speed_submarine = 0.007f;
const float speed_bomber = 0.02f;
const float speed_helicopter = 0.005f;

const float damage_mg = 0.05f;
const float damage_topedo = 1.0f;
const float damage_depth_charge = 3.0f;

std::vector<float> patrol_shape{
    0.0f, 0.0f, // bottom left
    2.0f, 0.0f, // bottom right
    2.0f, 0.1f, // top right
    0.0f, 0.1f  // top left
};
std::vector<float> destroyer_shape{
    0.0f, 0.0f, // bottom left
    3.0f, 0.0f, // bottom right
    3.0f, 0.2f, // top right
    0.0f, 0.2f  // top left
};
std::vector<float> submarine_shape{
    0.0f, -0.4f, // bottom left
    2.0f, -0.4f, // bottom right
    2.0f, -0.3f, // top right
    0.0f, -0.3f  // top left
};
std::vector<float> bomber_shape{
    0.0f, 0.5f, // bottom left
    2.0f, 0.5f, // bottom right
    2.0f, 0.6f, // top right
    0.0f, 0.6f  // top left
};
std::vector<float> helicopter_shape{
    0.0f, 0.4f, // bottom left
    1.0f, 0.4f, // bottom right
    1.0f, 0.5f, // top right
    0.0f, 0.5f  // top left
};

Unit::Unit(std::string type, bool is_friendly) : type_(type)
{
     if (type_ == type_patrol)
     {
          health_ = health_patrol;
          speed_ = speed_patrol;
          shape_ = patrol_shape;
     }
     else if (type_ == type_destroyer)
     {
          health_ = health_destroyer;
          speed_ = speed_destroyer;
          shape_ = destroyer_shape;
     }
     else if (type_ == type_submarine)
     {
          health_ = health_submarine;
          speed_ = speed_submarine;
          shape_ = submarine_shape;
     }
     else if (type_ == type_bomber)
     {
          health_ = health_bomber;
          speed_ = speed_bomber;
          shape_ = bomber_shape;
     }
     else if (type_ == type_helicopter)
     {
          health_ = health_helicopter;
          speed_ = speed_helicopter;
          shape_ = helicopter_shape;
     }

     // Hopefully defenseless enough!
     damage_ = 0.001f;

     if (is_friendly)
     {
          pos_ = 0.0f;
     }
     else
     {
          pos_ = 100.0f;
     }
};

Unit::~Unit() = default;

void Unit::take_damage(float damage)
{
     health_ -= damage;
     if (health_ <= 0)
     {
          is_destroyed_ = true;
     }
};

void Unit::attack(Unit &other)
{
     if (type_ == type_patrol)
     {
          // add 0.1s delay
          // std::this_thread::sleep_for(std::chrono::milliseconds(100));
          if (other.type_ == type_bomber || other.type_ == type_helicopter)
          {
               if (!shouldOccur(0.8f))
               {
                    return;
               }
               damage_ = damage_mg;
          }
          else if (other.type_ != type_submarine)
          {
               damage_ = damage_mg;
          }
     }
     else if (type_ == type_destroyer)
     {
          if (other.type_ != type_submarine)
          {
               // std::this_thread::sleep_for(std::chrono::milliseconds(100));
               if (other.type_ == type_bomber || other.type_ == type_helicopter)
               {
                    if (!shouldOccur(0.8f))
                    {
                         return;
                    }
               }

               damage_ = damage_mg;
          }
          else
          {
               // damages may be inflicted 20%, 50%, 100% on submarines
               // std::this_thread::sleep_for(std::chrono::seconds(3));
               float random_value = std::rand() / static_cast<float>(RAND_MAX);
               if (random_value < 0.2f)
               {
                    damage_ = 0.2f * damage_depth_charge; // 20% damage
               }
               else if (random_value < 0.7f)
               {
                    damage_ = 0.5f * damage_depth_charge; // 50% damage
               }
               else
               {
                    damage_ = damage_depth_charge; // 100% damage
               }
          }
     }
     else if (type_ == type_submarine)
     {
          if (other.type_ != type_bomber || other.type_ != type_helicopter)
          {
               // std::this_thread::sleep_for(std::chrono::seconds(3));
               damage_ = damage_topedo;
          }
     }
     else if (type_ == type_helicopter)
     {
          if (other.type_ == type_submarine)
          {
               float random_value = std::rand() / static_cast<float>(RAND_MAX);
               if (random_value < 0.2f)
               {
                    damage_ = 0.2f * damage_depth_charge; // 20% damage
               }
               else if (random_value < 0.7f)
               {
                    damage_ = 0.5f * damage_depth_charge; // 50% damage
               }
               else
               {
                    damage_ = damage_depth_charge; // 100% damage
               }
          }
          else
          {
               if (other.type_ == type_helicopter || other.type_ == type_bomber)
               {
                    if (!shouldOccur(0.8f))
                    {
                         return;
                    }
               }
               damage_ = damage_mg;
          }
     }
     else if (type_ == type_bomber)
     {
          if (other.type_ != type_bomber || other.type_ != type_helicopter)
          {
               damage_ = damage_topedo;
          }
     }

     other.take_damage(damage_);
};

void Unit::attack(NavalBase &other)
{
     if (type_ == type_patrol || type_ == type_destroyer || type_ == type_helicopter)
     {
          damage_ = damage_mg;
     }
     else
     {
          damage_ = damage_topedo;
     }

     other.take_damage(damage_);
}

void Unit::move(float direction)
{
     pos_ += direction;
};

bool Unit::is_destroyed()
{
     return is_destroyed_;
};

float Unit::get_position()
{
     return pos_;
}

std::string Unit::get_type()
{
     return type_;
}

float Unit::get_speed()
{
     return speed_;
}

bool Unit::shouldOccur(float probability)
{
     // Obtain a random number from hardware
     std::random_device rd;
     // Seed the generator
     std::mt19937 gen(rd());
     // Generate a float number between 0.0 and 1.0
     std::uniform_real_distribution<> distr(0.0, 1.0);

     float random_value = distr(gen);
     return random_value < probability;
}

std::vector<float> Unit::get_window_position(RenderWindow &render_window)
{
     std::vector<float> window_position = shape_; // copy over the shape

     for (int i = 0; i < shape_.size(); i += 2)
     {                                   // Loop over the x values only
          window_position.at(i) += pos_; // to get the window position we simply add the offset to the shapes x values
     }

     return window_position;
}
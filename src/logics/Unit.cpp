#include "logics/Unit.hpp"
#include <iostream>

const std::string type_patrol = "Patrol Boat";
const std::string type_destroyer = "Destroyer";
const std::string type_submarine = "Submarine";
const std::string type_bomber = "Bomber";
const std::string type_helicopter = "Helicopter";

const float health_patrol = 100.0f;
const float health_destroyer = 100.0f;
const float health_submarine = 100.0f;
const float health_bomber = 100.0f;
const float health_helicopter = 100.0f;

const float speed_patrol = 0.01f;
const float speed_destroyer = 0.001f;
const float speed_submarine = 0.005f;
const float speed_bomber = 0.01f;
const float speed_helicopter = 0.005f;

const float damage_patrol = 0.5f;
const float damage_destroyer = 0.5f;
const float damage_submarine = 0.5f;
const float damage_bomber = 0.5f;
const float damage_helicopter = 0.5f;


std::vector<float> patrol_shape {
     0.0f, 0.0f, // bottom left
     2.0f, 0.0f, // bottom right
     2.0f, 0.1f, // top right
     0.0f, 0.1f // top left
};
std::vector<float> destroyer_shape {
     0.0f, 0.0f,  // bottom left
     3.0f, 0.0f,  // bottom right
     3.0f, 0.2f,  // top right
     0.0f, 0.2f  // top left
};
std::vector<float> submarine_shape {
     0.0f, -0.4f,  // bottom left
     2.0f, -0.4f,  // bottom right
     2.0f, -0.3f,  // top right
     0.0f, -0.3f  // top left
};
std::vector<float> bomber_shape {
     0.0f, 0.5f,  // bottom left
     2.0f, 0.5f,  // bottom right
     2.0f, 0.6f,  // top right
     0.0f, 0.6f  // top left
};
std::vector<float> helicopter_shape {
     0.0f, 0.4f,  // bottom left
     1.0f, 0.4f,  // bottom right
     1.0f, 0.5f,  // top right
     0.0f, 0.5f  // top left
};
 
Unit::Unit(std::string type, bool is_friendly): type_(type){
   if(type_ == type_patrol){
        health_ = health_patrol;
        speed_ = speed_patrol;
        damage_ = damage_patrol;  
        shape_ = patrol_shape;    
   }else if(type_ == type_destroyer){
        health_ = health_destroyer;
        speed_ = speed_destroyer;
        damage_ = damage_destroyer;  
        shape_ = destroyer_shape;   
   }else if(type_ == type_submarine){
        health_ = health_submarine;
        speed_ = speed_submarine;
        damage_ = damage_submarine;
        shape_ = submarine_shape;      
   }else if(type_ == type_bomber){
        health_ = health_bomber;
        speed_ = speed_bomber;
        damage_ = damage_bomber; 
        shape_ = bomber_shape;     
   }else if(type_ == type_helicopter){
        health_ = health_helicopter;
        speed_ = speed_helicopter;
        damage_ = damage_helicopter;
        shape_ = helicopter_shape;      
   }

   if(is_friendly){
        pos_ = 10.0f;
   }else{
        pos_ = 90.0f;
   }
};

Unit::~Unit() = default;

void Unit::take_damage(float damage){
    health_ -= damage;
    if (health_ <= 0){
        is_destroyed_ = true;
    }
};

void Unit::attack(Unit& other){
    other.take_damage(damage_);

};

void Unit::attack(NavalBase& other) {
     other.take_damage(damage_);
}
        
void Unit::move(float direction){
    pos_+=direction;
};
        
bool Unit::is_destroyed(){
    return is_destroyed_;
};

float Unit::get_position() {
     return pos_;
}

std::string Unit::get_type() {
     return type_;
}

float Unit::get_speed() {
     return speed_;
}

std::vector<float> Unit::get_window_position(RenderWindow &render_window) {
     std::vector<float> window_position = shape_; // copy over the shape
     
     for (int i = 0; i < shape_.size(); i += 2) { // Loop over the x values only
          window_position.at(i) += pos_; // to get the window position we simply add the offset to the shapes x values
     }

     return window_position;
}
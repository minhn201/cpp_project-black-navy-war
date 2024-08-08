#include "logics/Unit.hpp"

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

const float speed_patrol = 0.10f;
const float speed_destroyer = 0.10f;
const float speed_submarine = 0.10f;
const float speed_bomber = 0.10f;
const float speed_helicopter = 0.10f;

const float damage_patrol = 5.0f;
const float damage_destroyer = 5.0f;
const float damage_submarine = 5.0f;
const float damage_bomber = 5.0f;
const float damage_helicopter = 5.0f;

 
Unit::Unit(std::string type, bool is_friendly): type_(type){
   if(type_ == type_patrol){
        health_ = health_patrol;
        speed_ = speed_patrol;
        damage_ = damage_patrol;      
   }else if(type_ == type_destroyer){
        health_ = health_destroyer;
        speed_ = speed_destroyer;
        damage_ = damage_destroyer;      
   }else if(type_ == type_submarine){
        health_ = health_submarine;
        speed_ = speed_submarine;
        damage_ = damage_submarine;      
   }else if(type_ == type_bomber){
        health_ = health_bomber;
        speed_ = speed_bomber;
        damage_ = damage_bomber;      
   }else if(type_ == type_helicopter){
        health_ = health_helicopter;
        speed_ = speed_helicopter;
        damage_ = damage_helicopter;      
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
        
void Unit::move(float direction){
    pos_+=direction;
};
        
bool Unit::is_destroyed(){
    return is_destroyed_;
};
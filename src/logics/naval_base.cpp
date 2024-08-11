#include "logics/naval_base.hpp"
#include <iostream>

// default constructor
NavalBase::NavalBase() {
    max_health_ = 5000.0f;
    health_ = 5000.0f;
    regeneration_ = 0.5f;
    is_destroyed_ = false;
}


// Decreases the bases health by the amount specified in damage
void NavalBase::take_damage(float damage) {
    if (is_destroyed_) {
        return;
    }
    health_ -= damage;
    
    if (health_ <= 0.0f) {
        is_destroyed_ = true;
    }
}

// Returns the amount of health that the base curretly has
float NavalBase::get_health() {
    return health_;
}

float NavalBase::get_max_health() {
    return max_health_;
}

// returns true if the base has been destroyed
bool NavalBase::is_destroyed() {
    return is_destroyed_;
}

// Regenerates the bases health by the value of the regeneration data member
void NavalBase::regenerate_health() {
    if (health_ >= max_health_) { // Don't want to increase health if it is already max
        return;
    }

    health_ += regeneration_;
}

// Increases the maximum amount of health that the base has
void NavalBase::upgrade_health() {
    max_health_ += 1000.0f;
}

// Increases the speed in which the base regenerates health
void NavalBase::upgrade_regeneration() {
    regeneration_ += 1.0f;
}
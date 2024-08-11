#include "logics/resources.hpp"
#include <iostream>


Resources::Resources() {
    resources_ = 0.0f;
    max_resources_ = 400.0f;
    income_ = 0.1f;
}

// Returns the current amount of resources 
float Resources::get_resources() const {
    return resources_;
}

// Increases resources by the amount of income if resources are not already full
void Resources::generate_income() {
    if (resources_ >= max_resources_) { // Don't do anything if already at max resources
        return;
    }
    resources_ += income_;
}

// Decreases resources by the amount specified by cost
void Resources::purchase(float cost) {
    resources_ -= cost;
}

// Increases the maximum resources
void Resources::upgrade_max_resources() {
    max_resources_ *= 2.0f;
}

// Increases the income genereated per second
void Resources::upgrade_income() {
    income_ += 0.1f;
}
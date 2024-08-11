#ifndef NAVAL_BASE_HPP
#define NAVAL_BASE_HPP

class NavalBase {
    private:
        float health_;
        float max_health_;
        float regeneration_;
        bool is_destroyed_;

    public:
        // default constructor
        NavalBase();

        // Decreases the bases health by the amount specified in damage
        void take_damage(float damage);

        // Returns the amount of health that the base curretly has
        float get_health();

        float get_max_health();

        // returns true if the base has been destroyed
        bool is_destroyed();

        // Regenerates the bases health by the value of the regeneration data member
        void regenerate_health();

        // Increases the maximum amount of health that the base has
        void upgrade_health();

        // Increases the speed in which the base regenerates health
        void upgrade_regeneration();
};

#endif
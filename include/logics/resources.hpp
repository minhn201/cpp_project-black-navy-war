#ifndef RESOURCES_HPP
#define RESOURCES_HPP

class Resources {
    private:
        float resources_;
        float max_resources_;
        float income_;

    public:
        // default constructor
        Resources();

        // Returns the current amount of resources 
        float get_resources() const;

        // Increases resources by the amount of income if resources are not already full
        void generate_income();

        // Decreases resources by the amount specified by cost
        void purchase(float cost);

        // Increases the maximum resources
        void upgrade_max_resources();

        // Increases the income genereated per second
        void upgrade_income();
};

#endif
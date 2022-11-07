#ifndef SWARM_SEARCH
#define SWARM_SEARCH

#include <ctime>
#include <random>
#include <vector>
#include <cfloat>
#include <functional>

#include "utilities.hpp"

struct Particle
{
    std::vector<double> position;
    std::vector<double> velocity;
    SearchResult bestLocalResult;
};

class SwarmSearch
{
public:
    SwarmSearch(
        std::function<double(Point)> &objective_func,
        size_t n,
        size_t particle_count,
        int threads = 4,
        double min_x = -40,
        double max_x = 40
    );

    static void setSeed(int thread_id);

    SearchResult search(size_t iterations);

    void plot(size_t iterations, double animation_speed = 1.0 / 0.01);

    static thread_local std::mt19937 random_engine;
private:
    std::function<double(Point)> objective_func;
    size_t n;
    size_t particle_count;
    int threads;
    double min_x;
    double max_x;

    double c1 = 1;
    const double c2 = 0.8, c3 = 0.8;
    SearchResult best_global_result;
    std::vector<Particle> particles;
    std::uniform_real_distribution<double> unif01 = std::uniform_real_distribution<double>(0, 1);

    void init();
    void updateParticle(Particle& particle);
    void updateVelocity(Particle& particle);
};


#endif
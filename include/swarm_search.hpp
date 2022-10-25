#ifndef SWARM_SEARCH
#define SWARM_SEARCH

#include <time.h>
#include <random>
#include <vector>
#include <float.h>

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
    SwarmSearch() {setSeed();};
    SwarmSearch(int seed) {setSeed(seed);};
    void setSeed(int seed = time(NULL));
    SearchResult search(std::vector<double>&minX, std::vector<double>&maxX, size_t particlesNumber, size_t iterations);
    static thread_local std::mt19937 random_engine;
private:
    SearchResult bestGlobalResult;
    std::vector<Particle>particles;
    std::uniform_real_distribution<double> unif01 = std::uniform_real_distribution<double>(0, 1);

    void init(size_t particlesNumber, std::vector<double>&minX, std::vector<double>&maxX);
    void updateParticle(Particle& particle);
    void updateVelocity(Particle& particle);
    double c1 = 1;
    const double c2 = 0.8, c3 = 0.8;
};


#endif
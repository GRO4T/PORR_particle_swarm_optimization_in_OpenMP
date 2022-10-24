#include "swarm_search.hpp"

#include "test_functions.hpp"

#include <float.h>
#include <cassert>
#include <chrono>

void SwarmSearch::setSeed(int seed /*= time(NULL)*/)
{
    random_engine = std::default_random_engine(seed);
}

SearchResult SwarmSearch::search(std::vector<double>&minX, std::vector<double>&maxX, size_t particlesNumber, size_t iterations)
{
    assert((minX.size() == maxX.size()) && "Different dimensions in range of domain");
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    bestGlobalResult.result = DBL_MAX;
    for(auto x : minX)
        bestGlobalResult.x.push_back(DBL_MAX);

    init(particlesNumber, minX, maxX);

    for(size_t i = 0; i < iterations; ++i)
    {
        for(size_t j = 0; j < particlesNumber; ++j)
        {
            updateParticle(particles[j]);
        }
        c1 *= 0.992;
    }
    
    bestGlobalResult.time = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::steady_clock::now() - begin).count();
    return bestGlobalResult;
}

void SwarmSearch::init(size_t particlesNumber, std::vector<double>&minX, std::vector<double>&maxX)
{
    for(size_t i = 0; i < particlesNumber; ++i)
    {
        Particle particle;
        for(unsigned int i = 0; i < minX.size(); ++i)
        {
            auto unif = std::uniform_real_distribution<double>(minX[i], maxX[i]);
            particle.position.push_back(unif(random_engine));
            particle.velocity.push_back(0.0);
            particle.bestLocalResult.x.push_back(DBL_MAX);
        }
        particle.bestLocalResult.result = DBL_MAX;
        particles.push_back(particle);
    }
}

void SwarmSearch::updateParticle(Particle& particle)
{
    for(size_t i = 0; i < particle.position.size(); ++i)
    {
        particle.position[i] += particle.velocity[i];
        // "odbijanie" od ściany
        if(particle.position[i] > 40)
            particle.position[i] = 40 - (particle.position[i] - 40); // "odbijanie" od ściany
        if(particle.position[i] < -40)
            particle.position[i] = -40 + (-40 - particle.position[i]);
    }
    double result = testFunc1(particle.position);
    if(result < particle.bestLocalResult.result)
    {
        particle.bestLocalResult.result = result;
        particle.bestLocalResult.x = particle.position;
    }
    if(result < bestGlobalResult.result)
    {
        bestGlobalResult.result = result;
        bestGlobalResult.x = particle.position;
    }
    updateVelocity(particle);
}

void SwarmSearch::updateVelocity(Particle& particle)
{
    for(size_t i = 0; i < particle.velocity.size(); ++i)
    {
        double r1 = unif01(random_engine), r2 = unif01(random_engine), r3 = unif01(random_engine);
        particle.velocity[i] = c1*r1*particle.velocity[i] + c2*r2*(particle.bestLocalResult.x[i] - particle.position[i]) + c3*r3*(bestGlobalResult.x[i] - particle.position[i]);
    }
}

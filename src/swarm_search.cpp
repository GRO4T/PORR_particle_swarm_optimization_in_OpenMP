#include "swarm_search.hpp"

#include "test_functions.hpp"

#include <float.h>
#include <cassert>
#include <chrono>
#include <omp.h>

thread_local std::mt19937 SwarmSearch::random_engine;

SwarmSearch::SwarmSearch(
    std::function<double(Point)> objective_func,
    size_t n,
    size_t particle_count,
    int threads,
    double min_x,
    double max_x,
    int seed
):      objective_func(objective_func),
        n(n),
        particle_count(particle_count),
        threads(threads),
        min_x(min_x),
        max_x(max_x) {
    setSeed(seed);
    omp_set_num_threads(threads);
}

void SwarmSearch::setSeed(int seed /*= time(NULL)*/)
{
    random_engine = std::mt19937(seed);
}

SearchResult SwarmSearch::search(size_t iterations)
{
    auto begin = std::chrono::steady_clock::now();

    best_global_result.result = DBL_MAX;
    for(size_t i = 0; i < n; ++i)
        best_global_result.x.push_back(DBL_MAX);

    init();

    #ifdef OPENMP_ENABLED
        #pragma omp parallel for shared(best_global_result, c1)
    #endif
    for(size_t i = 0; i < iterations; ++i)
    {
        for(size_t j = 0; j < particle_count; ++j)
        {
            updateParticle(particles[j]);
        }
        c1 *= 0.992;
    }

    auto end = std::chrono::steady_clock::now();
    best_global_result.time = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
    return best_global_result;
}

void SwarmSearch::init()
{
    for(size_t i = 0; i < particle_count; ++i)
    {
        Particle particle;
        for(size_t i = 0; i < n; ++i)
        {
            auto unif = std::uniform_real_distribution<double>(min_x, max_x);
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

    #ifdef OPENMP_ENABLED
    #pragma omp critical
    {
    #endif
        if(result < best_global_result.result)
        {
            best_global_result.result = result;
            best_global_result.x = particle.position;
        }
    #ifdef OPENMP_ENABLED
    }
    #endif

    updateVelocity(particle);
}

void SwarmSearch::updateVelocity(Particle& particle)
{
    for(size_t i = 0; i < particle.velocity.size(); ++i)
    {
        double r1 = unif01(random_engine), r2 = unif01(random_engine), r3 = unif01(random_engine);
        particle.velocity[i] = c1*r1 * particle.velocity[i]
                             + c2*r2 * (particle.bestLocalResult.x[i] - particle.position[i])
                             + c3*r3 * (best_global_result.x[i] - particle.position[i]);
    }
}

#include "swarm_search.hpp"

#include "test_functions.hpp"
#include "plots.hpp"

#include <cfloat>
#include <cassert>
#include <chrono>
#include <omp.h>
#include <unistd.h>

thread_local std::mt19937 SwarmSearch::random_engine;

SwarmSearch::SwarmSearch(
    std::function<double(Point)> &objective_func,
    size_t n,
    size_t particle_count,
    int threads,
    double min_x,
    double max_x
):      objective_func(objective_func),
        n(n),
        particle_count(particle_count),
        threads(threads),
        min_x(min_x),
        max_x(max_x) {
    random_engine = std::mt19937(time(nullptr) + getpid());
}

void SwarmSearch::setSeed(int thread_id)
{
    random_engine = std::mt19937(time(nullptr) + thread_id + getpid());
}

SearchResult SwarmSearch::search(size_t iterations)
{
    omp_set_num_threads(threads);
    
    auto begin = std::chrono::steady_clock::now();

    best_global_result.result = DBL_MAX;
    for(size_t i = 0; i < n; ++i)
        best_global_result.x.push_back(DBL_MAX);

    init();

    #ifdef OPENMP_ENABLED
        #pragma omp parallel
    {
        setSeed(omp_get_thread_num());
    }
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
        for(size_t j = 0; j < n; ++j)
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

void SwarmSearch::plot(size_t iterations, double animation_speed) {
    assert(n == 2);

    best_global_result.result = DBL_MAX;
    for(size_t i = 0; i < n; ++i)
        best_global_result.x.push_back(DBL_MAX);

    init();

    for(size_t i = 0; i < iterations; ++i)
    {
        plotClear();

        for(size_t j = 0; j < particle_count; ++j)
        {
            Particle& particle = particles[j];

            for(size_t k = 0; k < particle.position.size(); ++k)
            {
                particle.position[k] += particle.velocity[k];
                // "odbijanie" od ściany
                if(particle.position[k] > 40)
                    particle.position[k] = 40 - (particle.position[k] - 40); // "odbijanie" od ściany
                if(particle.position[k] < -40)
                    particle.position[k] = -40 + (-40 - particle.position[k]);
            }

            double result = testFunc1(particle.position);

            if(result < particle.bestLocalResult.result)
            {
                particle.bestLocalResult.result = result;
                particle.bestLocalResult.x = particle.position;
            }

            if(result < best_global_result.result)
            {
                best_global_result.result = result;
                best_global_result.x = particle.position;
            }

            updateVelocity(particle);
        }
        c1 *= 0.992;

        std::cout << "-------------------------------" << std::endl;
        std::cout << "iteration: " << i << std::endl;
        std::cout << "best_result: " << best_global_result.result << std::endl;
        std::cout << "best_position: (" << best_global_result.x[0] << ", " << best_global_result.x[1] << ")" << std::endl;

        std::vector<double> x, y, u, v;
        for (const auto& particle: particles) {
            x.push_back(particle.position[0]);
            y.push_back(particle.position[1]);
            u.push_back(particle.velocity[0]);
            v.push_back(particle.velocity[1]);
        }
        plotContourWithQuiver(objective_func, best_global_result.x, x, y, u, v, min_x, max_x, animation_speed);
    }
}
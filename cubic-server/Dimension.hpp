#ifndef CUBICSERVER_DIMENSION_HPP
#define CUBICSERVER_DIMENSION_HPP


#include <atomic>
#include <thread>
#include <vector>
#include <functional>

#include "logging/Logger.hpp"
#include "Entity.hpp"

class World;

class Entity;

class Dimension
{
public:
    Dimension(World *world): _world(world) {
        _log = logging::Logger::get_instance();
    }
    virtual void initialize();
    virtual void tick();
    virtual World *getWorld() const;
    virtual std::vector<Entity *> &getEntities();
    virtual void forEachEntity(std::function<void(Entity *)> callback);
    virtual void forEachEntityIf(std::function<void(Entity *)> callback, std::function<bool(Entity *)> predicate);

protected:
    std::vector<Entity *> _entities;
    logging::Logger *_log;
    World *_world;
    std::atomic<int> _numThreadsWaiting;
    std::mutex _processingMutex;
};


#endif //CUBICSERVER_DIMENSION_HPP

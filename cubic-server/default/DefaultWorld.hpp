#ifndef CUBICSERVER_DEFAULT_DEFAULTWORLD_HPP
#define CUBICSERVER_DEFAULT_DEFAULTWORLD_HPP

#include "../World.hpp"
#include "world_storage/ChunkColumn.hpp"

class DefaultWorld : public World {
public:
    DefaultWorld(std::shared_ptr<WorldGroup> worldGroup, world_storage::WorldType worldType);
    ~DefaultWorld() override = default;
    void tick() override;
    void initialize() override;
    void stop() override;
};

#endif // CUBICSERVER_DEFAULT_DEFAULTWORLD_HPP

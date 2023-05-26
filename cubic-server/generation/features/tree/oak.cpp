#include "oak.hpp"

#include <algorithm>
#include <vector>

#include "Server.hpp"
#include "blocks.hpp"
#include "generation/generator.hpp"
#include "logging/Logger.hpp"
#include "world_storage/ChunkColumn.hpp"
#include "world_storage/Section.hpp"

using namespace generation::trees;

std::deque<Position> &OakTree::getPosForTreeGeneration(void)
{
    using namespace world_storage;
    for (int z = 0; z < SECTION_WIDTH; z++) {
        for (int x = 0; x < SECTION_WIDTH; x++) {
            for (int y = CHUNK_HEIGHT_MAX - 5; CHUNK_HEIGHT_MIN <= y; y--) {
                auto block = _chunk.getBlock({x, y, z});
                if (block == Blocks::Air::toProtocol())
                    continue;
                else {
                    if (block == Blocks::GrassBlock::toProtocol(Blocks::GrassBlock::Properties::Snowy::FALSE) || block == Blocks::Dirt::toProtocol()) {
                        if (_generator.getNoise(x + _chunk.getChunkPos().x * SECTION_WIDTH, y, z + _chunk.getChunkPos().z * SECTION_WIDTH).noise3D.density > 0.5 &&
                            _generator.getBiome(x + _chunk.getChunkPos().x * SECTION_WIDTH, y, z + _chunk.getChunkPos().z * SECTION_WIDTH)) {
                            _positions.emplace_back(x, y + 1, z);
                        }
                    }
                    break;
                }
            }
        }
    }
    return _positions;
}

std::deque<Position> &OakTree::filterTreeGrowSpace()
{
    std::erase_if(_positions, [this](const Position &pos) {
        for (int i = 0; i <= _generator.getTreeSize(pos, {4, 6}); i++) {
            auto block = _chunk.getBlock({pos.x, pos.y + i, pos.z});
            if (block != Blocks::Air::toProtocol())
                return true;
        }
        return false;
    });
    return _positions;
}

void OakTree::generateTree()
{
    auto treeEmplacement = _positions.begin();
    auto tree = getTree(
        treeEmplacement->x + this->_chunk.getChunkPos().x * world_storage::SECTION_WIDTH, treeEmplacement->y,
        treeEmplacement->z + this->_chunk.getChunkPos().z * world_storage::SECTION_WIDTH
    );
    for (auto block : tree) {
        if (treeEmplacement->x + block.pos.x < 0 || treeEmplacement->x + block.pos.x >= world_storage::SECTION_WIDTH || treeEmplacement->z + block.pos.z < 0 ||
            treeEmplacement->z + block.pos.z >= world_storage::SECTION_WIDTH)
            continue;
        _chunk.updateBlock({treeEmplacement->x + block.pos.x, treeEmplacement->y + block.pos.y, treeEmplacement->z + block.pos.z}, block.block);
    }
}

const std::vector<generation::Generator::TreeBlock> OakTree::getTree(const Position &pos)
{
    std::vector<generation::Generator::TreeBlock> tree;
    auto treeSize = _generator.getTreeSize(pos, _treeSize);
    for (int y = 0; y <= treeSize + 1; y++) {
        if (y <= treeSize)
            tree.emplace_back(generation::Generator::TreeBlock {{0, y, 0}, Blocks::OakLog::toProtocol(Blocks::OakLog::Properties::Axis::Y)});
        if (y >= treeSize - 2 && y <= treeSize - 1) {
            for (int x = -2; x <= 2; x++) {
                for (int z = -2; z <= 2; z++) {
                    if (x == 0 && z == 0)
                        continue;
                    tree.emplace_back(generation::Generator::TreeBlock {
                        {x, y, z},
                        Blocks::OakLeaves::toProtocol(
                            Blocks::OakLeaves::Properties::Distance::ONE, Blocks::OakLeaves::Properties::Persistent::FALSE, Blocks::OakLeaves::Properties::Waterlogged::FALSE
                        )});
                }
            }
        }
        if (y >= treeSize) {
            for (int x = -1; x <= 1; x++) {
                for (int z = -1; z <= 1; z++) {
                    if (x == 0 && z == 0 && y == treeSize)
                        continue;
                    if (x * x == z * z)
                        continue;
                    tree.emplace_back(generation::Generator::TreeBlock {
                        {x, y, z},
                        Blocks::OakLeaves::toProtocol(
                            Blocks::OakLeaves::Properties::Distance::ONE, Blocks::OakLeaves::Properties::Persistent::FALSE, Blocks::OakLeaves::Properties::Waterlogged::FALSE
                        )});
                }
            }
        }
    }
    return tree;
}

const std::vector<generation::Generator::TreeBlock> OakTree::getTree(Generator::positionType x, Generator::positionType y, Generator::positionType z) { return getTree({x, y, z}); }

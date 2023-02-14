#include "DarkOakWallSign.hpp"
#include <stdexcept>

namespace Blocks {
    namespace DarkOakWallSign {
        BlockId toProtocol(Properties::Facing facing, Properties::Waterlogged waterlogged) {
            switch (facing) {
            case Properties::Facing::NORTH:
                switch (waterlogged) {
                case Properties::Waterlogged::TRUE:
                    return 4072;
                case Properties::Waterlogged::FALSE:
                    return 4073;
                }
            case Properties::Facing::SOUTH:
                switch (waterlogged) {
                case Properties::Waterlogged::TRUE:
                    return 4074;
                case Properties::Waterlogged::FALSE:
                    return 4075;
                }
            case Properties::Facing::WEST:
                switch (waterlogged) {
                case Properties::Waterlogged::TRUE:
                    return 4076;
                case Properties::Waterlogged::FALSE:
                    return 4077;
                }
            case Properties::Facing::EAST:
                switch (waterlogged) {
                case Properties::Waterlogged::TRUE:
                    return 4078;
                case Properties::Waterlogged::FALSE:
                    return 4079;
                }
            }
            return 0;
        }
        BlockId paletteToProtocol(std::vector<std::pair<std::string, std::string>> properties) {
            if (properties.size() != 2)
            throw std::runtime_error("Invalid number of properties");
            Properties::Facing facing;
            Properties::Waterlogged waterlogged;
            for (auto prop : properties) {
                if (prop.first == "facing") {
                    if (prop.second == "north") {
                        facing = Properties::Facing::NORTH;
                    } else if (prop.second == "south") {
                        facing = Properties::Facing::SOUTH;
                    } else if (prop.second == "west") {
                        facing = Properties::Facing::WEST;
                    } else if (prop.second == "east") {
                        facing = Properties::Facing::EAST;
                    } else {
                        throw std::runtime_error("Invalid property \"facing\" value");
                    }
                } else if (prop.first == "waterlogged") {
                    if (prop.second == "true") {
                        waterlogged = Properties::Waterlogged::TRUE;
                    } else if (prop.second == "false") {
                        waterlogged = Properties::Waterlogged::FALSE;
                    } else {
                        throw std::runtime_error("Invalid property \"waterlogged\" value");
                    }
                } else {
                    throw std::runtime_error("Invalid property name");
                }
            }
            return toProtocol(facing, waterlogged);
        }
    }

}

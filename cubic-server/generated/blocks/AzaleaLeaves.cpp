#include "AzaleaLeaves.hpp"
#include <stdexcept>

namespace Blocks {
    namespace AzaleaLeaves {
        BlockId toProtocol(Properties::Distance distance, Properties::Persistent persistent, Properties::Waterlogged waterlogged) {
            switch (distance) {
            case Properties::Distance::ONE:
                switch (persistent) {
                case Properties::Persistent::TRUE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 402;
                    case Properties::Waterlogged::FALSE:
                        return 403;
                    }
                case Properties::Persistent::FALSE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 404;
                    case Properties::Waterlogged::FALSE:
                        return 405;
                    }
                }
            case Properties::Distance::TWO:
                switch (persistent) {
                case Properties::Persistent::TRUE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 406;
                    case Properties::Waterlogged::FALSE:
                        return 407;
                    }
                case Properties::Persistent::FALSE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 408;
                    case Properties::Waterlogged::FALSE:
                        return 409;
                    }
                }
            case Properties::Distance::THREE:
                switch (persistent) {
                case Properties::Persistent::TRUE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 410;
                    case Properties::Waterlogged::FALSE:
                        return 411;
                    }
                case Properties::Persistent::FALSE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 412;
                    case Properties::Waterlogged::FALSE:
                        return 413;
                    }
                }
            case Properties::Distance::FOUR:
                switch (persistent) {
                case Properties::Persistent::TRUE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 414;
                    case Properties::Waterlogged::FALSE:
                        return 415;
                    }
                case Properties::Persistent::FALSE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 416;
                    case Properties::Waterlogged::FALSE:
                        return 417;
                    }
                }
            case Properties::Distance::FIVE:
                switch (persistent) {
                case Properties::Persistent::TRUE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 418;
                    case Properties::Waterlogged::FALSE:
                        return 419;
                    }
                case Properties::Persistent::FALSE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 420;
                    case Properties::Waterlogged::FALSE:
                        return 421;
                    }
                }
            case Properties::Distance::SIX:
                switch (persistent) {
                case Properties::Persistent::TRUE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 422;
                    case Properties::Waterlogged::FALSE:
                        return 423;
                    }
                case Properties::Persistent::FALSE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 424;
                    case Properties::Waterlogged::FALSE:
                        return 425;
                    }
                }
            case Properties::Distance::SEVEN:
                switch (persistent) {
                case Properties::Persistent::TRUE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 426;
                    case Properties::Waterlogged::FALSE:
                        return 427;
                    }
                case Properties::Persistent::FALSE:
                    switch (waterlogged) {
                    case Properties::Waterlogged::TRUE:
                        return 428;
                    case Properties::Waterlogged::FALSE:
                        return 429;
                    }
                }
            }
            return 0;
        }
        BlockId paletteToProtocol(std::vector<std::pair<std::string, std::string>> properties) {
            if (properties.size() != 3)
            throw std::runtime_error("Invalid number of properties");
            Properties::Distance distance;
            Properties::Persistent persistent;
            Properties::Waterlogged waterlogged;
            for (auto prop : properties) {
                if (prop.first == "distance") {
                    if (prop.second == "1") {
                        distance = Properties::Distance::ONE;
                    } else if (prop.second == "2") {
                        distance = Properties::Distance::TWO;
                    } else if (prop.second == "3") {
                        distance = Properties::Distance::THREE;
                    } else if (prop.second == "4") {
                        distance = Properties::Distance::FOUR;
                    } else if (prop.second == "5") {
                        distance = Properties::Distance::FIVE;
                    } else if (prop.second == "6") {
                        distance = Properties::Distance::SIX;
                    } else if (prop.second == "7") {
                        distance = Properties::Distance::SEVEN;
                    } else {
                        throw std::runtime_error("Invalid property \"distance\" value");
                    }
                } else if (prop.first == "persistent") {
                    if (prop.second == "true") {
                        persistent = Properties::Persistent::TRUE;
                    } else if (prop.second == "false") {
                        persistent = Properties::Persistent::FALSE;
                    } else {
                        throw std::runtime_error("Invalid property \"persistent\" value");
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
            return toProtocol(distance, persistent, waterlogged);
        }
    }

}

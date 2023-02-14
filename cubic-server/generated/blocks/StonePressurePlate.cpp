#include "StonePressurePlate.hpp"
#include <stdexcept>

namespace Blocks {
    namespace StonePressurePlate {
        BlockId toProtocol(Properties::Powered powered) {
            switch (powered) {
            case Properties::Powered::TRUE:
                return 4112;
            case Properties::Powered::FALSE:
                return 4113;
            }
            return 0;
        }
        BlockId paletteToProtocol(std::vector<std::pair<std::string, std::string>> properties) {
            if (properties.size() != 1)
            throw std::runtime_error("Invalid number of properties");
            Properties::Powered powered;
            for (auto prop : properties) {
                if (prop.first == "powered") {
                    if (prop.second == "true") {
                        powered = Properties::Powered::TRUE;
                    } else if (prop.second == "false") {
                        powered = Properties::Powered::FALSE;
                    } else {
                        throw std::runtime_error("Invalid property \"powered\" value");
                    }
                } else {
                    throw std::runtime_error("Invalid property name");
                }
            }
            return toProtocol(powered);
        }
    }

}

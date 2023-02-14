#include "LightGrayCandleCake.hpp"
#include <stdexcept>

namespace Blocks {
    namespace LightGrayCandleCake {
        BlockId toProtocol(Properties::Lit lit) {
            switch (lit) {
            case Properties::Lit::TRUE:
                return 18603;
            case Properties::Lit::FALSE:
                return 18604;
            }
            return 0;
        }
        BlockId paletteToProtocol(std::vector<std::pair<std::string, std::string>> properties) {
            if (properties.size() != 1)
            throw std::runtime_error("Invalid number of properties");
            Properties::Lit lit;
            for (auto prop : properties) {
                if (prop.first == "lit") {
                    if (prop.second == "true") {
                        lit = Properties::Lit::TRUE;
                    } else if (prop.second == "false") {
                        lit = Properties::Lit::FALSE;
                    } else {
                        throw std::runtime_error("Invalid property \"lit\" value");
                    }
                } else {
                    throw std::runtime_error("Invalid property name");
                }
            }
            return toProtocol(lit);
        }
    }

}

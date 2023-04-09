#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Blocks {
typedef int32_t BlockId;

namespace TallGrass {
namespace Properties {
enum class Half {
    UPPER,
    LOWER
};
}
BlockId toProtocol(Properties::Half half);
}

}

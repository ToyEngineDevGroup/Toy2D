#include "runtime/core/base/layer.h"

namespace Toy2D {
    Layer::Layer(const std::string& debugName) :
        m_debug_name(debugName) {
    }

    Layer::~Layer() {
    }
} // namespace Toy2D
#pragma once

#include "runtime/core/util/singleton.h"

#define GET_FILE_DIALOG() ::Toy2D::FileDialog::getInstance()

namespace Toy2D {
    class FileDialog : public Singleton<FileDialog> {
    public:
        std::string openFile(const char* filter);
        std::string saveFile(const char* filter);
    };
} // namespace Toy2D
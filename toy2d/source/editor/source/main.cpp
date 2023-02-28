#include "editor.h"

int main(int /*argc*/, char** /*argv*/) {
    auto editor_app = Toy2D::createApp();

    editor_app->run();

    delete editor_app;
}

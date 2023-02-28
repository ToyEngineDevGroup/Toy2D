#pragma once

namespace Toy2D {
    class InputSystem {
    public:
        static bool isKeyPressed(int keycode);

        static bool    isMouseButtonPressed(int button);
        static Vector2 getMousePosition();
        static float   getMouseX();
        static float   getMouseY();
    };
} // namespace Toy2D
#ifndef GLRENDERENGINE_H
#define GLRENDERENGINE_H

#include <linalg/color.h>

namespace nb {
    namespace opengl {

        class GLRenderEngine {
        public:
            GLRenderEngine();
            static void Init();

            static void SetViewPort(int x, int y, int width, int height);

            static void SetClearColor(const nb::linalg::Color& color);

        };
    }
}
#endif //GLRENDERENGINE_H

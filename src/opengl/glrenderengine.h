#ifndef GLRENDERENGINE_H
#define GLRENDERENGINE_H

namespace nb {
    namespace opengl {

        class GLRenderEngine {
        public:
            GLRenderEngine();
            static void Init();

            static void PreRender(int x, int y, int width, int height);

        };
    }
}
#endif //GLRENDERENGINE_H

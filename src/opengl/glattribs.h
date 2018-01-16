#ifndef GLATTRIBS_H
#define GLATTRIBS_H

#include <vector>
#include <unordered_map>

using namespace std;

namespace nb {
namespace opengl {

class GLBooleanAttrib {
public:
    GLBooleanAttrib() {}
    virtual ~GLBooleanAttrib() {}

    virtual void Enable() = 0;
    virtual void Disable() = 0;

    bool value() { return mFlag;}

protected:
    bool mFlag;
};


class GLAttribDepthTest : public GLBooleanAttrib {
public:
    GLAttribDepthTest();
    virtual ~GLAttribDepthTest() {}

    void Enable();
    void Disable();
};

////////////////////////////////////////////////////////
class GLStoreAllAttributes : public GLBooleanAttrib {
public:
    GLStoreAllAttributes();
    virtual ~GLStoreAllAttributes() {}

    void Enable();
    void Disable();

protected:
    bool mStored;
};
////////////////////////////////////////////////////////
class GLScopedAttributeStorage : public GLStoreAllAttributes {
public:
    GLScopedAttributeStorage();
    virtual ~GLScopedAttributeStorage();
};

}
}

#endif // GLATTRIBS_H

//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#include "glmeshbuffer.h"
#include "glselect.h"

namespace nb {
namespace opengl {

GLMeshBuffer::GLMeshBuffer()
{
    mPolygonRenderMode = glRenderModeFill;
}

GLMeshBuffer::~GLMeshBuffer()
{
    Clear();
}

void GLMeshBuffer::Bind()
{
    glPolygonMode(GL_FRONT_AND_BACK, GLenum(mPolygonRenderMode));

    //3. bind all vertex attributes
    for(U32 i=0; i < mVertexAttribs.size(); i++) {
        mVertexAttribs[i]->Bind();
    }

    //4. bind all face attributes
    for(U32 i=0; i < mFaceArrays.size(); i++) {
        mFaceArrays[i]->Bind();
    }

}

void GLMeshBuffer::Unbind()
{
    //1. unbind all face attributes
    for(U32 i=0; i < mFaceArrays.size(); i++) {
        mFaceArrays[i]->Unbind();
    }

    //2. unbind all vertex attributes
    for(U32 i=0; i < mVertexAttribs.size(); i++) {
        mVertexAttribs[i]->Unbind();
    }

}

void GLMeshBuffer::Clear()
{
    mVertexAttribs.resize(0);
    mFaceArrays.resize(0);
}

GLMeshBuffer::GLVertexArrayPtrType GLMeshBuffer::AddVertexAttribArray()
{
    GLVertexArrayPtrType vertexarray(new GLVertexArray());
    mVertexAttribs.push_back(vertexarray);
    return vertexarray;
}

GLMeshBuffer::GLVertexArrayPtrType GLMeshBuffer::GetVertexAttribArray(U32 index)
{
    if(IsVertexAttribArrayIndex(index))
        return mVertexAttribs[index];
    else
        return NULL;
}

U32 GLMeshBuffer::CountVertexAttribArrays() const
{
    return (U32)mVertexAttribs.size();
}

GLMeshBuffer::GLFaceArrayPtrType GLMeshBuffer::AddFaceArray()
{
    GLFaceArrayPtrType facearray(new GLFaceArray());
    mFaceArrays.push_back(facearray);
    return facearray;
}

GLMeshBuffer::GLFaceArrayPtrType GLMeshBuffer::GetFaceArray(U32 index)
{
    if(IsFaceArrayIndex(index))
        return mFaceArrays[index];
    else
        return NULL;
}

U32 GLMeshBuffer::CountFaceArrays() const
{
    return (U32)mFaceArrays.size();
}

void GLMeshBuffer::SetPolygonRenderMode(GLPolygonMode mode)
{
    mPolygonRenderMode = mode;
}

bool GLMeshBuffer::IsVertexAttribArrayIndex(U32 index) const
{
    return (index < mVertexAttribs.size());
}

bool GLMeshBuffer::IsFaceArrayIndex(U32 index) const
{
    return (index < mFaceArrays.size());
}

}
}

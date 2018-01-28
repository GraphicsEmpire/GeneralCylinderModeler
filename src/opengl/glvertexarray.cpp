//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#include "glvertexarray.h"
#include "glselect.h"
#include "utils/logger.h"

using namespace nb::utils;

namespace nb {
namespace opengl {

GLVertexArray::GLVertexArray() {
  //use to flag if initialization is complete
  mValid = false;
  mVertexArrayObject = 0;
}

GLVertexArray::~GLVertexArray() {
    clear();
}

bool GLVertexArray::Import(const vector<GLVertexAttribute>& attribs,
                            const vector<float>& vdata,
                            GLVertexAttributeLayoutType layout)
{
    if(attribs.size() == 0 || vdata.size() == 0) {
        nbLogError("Invalid vertex input");
        return false;
    }

    //check layout
    U32 vertex_packet_size = 0;
    //sum up the dimension of all attributes in this layout
    for(U32 i=0; i < attribs.size(); i++) {
        vertex_packet_size += attribs[i].GetCount();
    }

    U32 rem = vdata.size() % vertex_packet_size;
    if(rem != 0) {
        nbLogError("VertexBuffer layout does not cover the entire data buffer. rem = %u", rem);
        return false;
    }

    //count the number of vertices supplied
    U32 count_vertices = vdata.size() / vertex_packet_size;

    //clear
    clear();

    //generate vertex array
    glGenVertexArrays(1, &mVertexArrayObject);

    //1. bind the vao
    glBindVertexArray(mVertexArrayObject);


    //create the only vertex buffer object
    U32 vbo = 0;
    glGenBuffers(1, &vbo);
    mVertexBufferObjects.push_back(vbo);

    //2. copy data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vdata.size(),
                 vdata.data(), GL_STATIC_DRAW);

    //loop over attribs count
    U64 prev_batch_bytes_offset = 0;
    for(U32 i=0; i < attribs.size(); i++) {
        U64 byte_offset = 0;
        if(layout == kInterleave) {
            byte_offset = attribs[i].GetCount() * sizeof(float);
        }
        else if(layout == kSequentialBatch) {
            byte_offset = prev_batch_bytes_offset;
        }

        //3. set vertex attrib array
        glEnableVertexAttribArray(attribs[i].GetVertexAttributeIndex());
        glVertexAttribPointer(attribs[i].GetVertexAttributeIndex(),
                              attribs[i].GetCount(),
                              GL_FLOAT,
                              GL_FALSE,
                              vertex_packet_size * sizeof(float),
                              (GLvoid*)(byte_offset));

        //accumulate offset
        prev_batch_bytes_offset += count_vertices * attribs[i].GetCount() * sizeof(float);
    } //attribs

    //4. unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //5. unbind the vao
    glBindVertexArray(0);

    mValid = true;
    return true;
}

void GLVertexArray::Bind() {
    if(!mValid)
        return;

    glBindVertexArray(mVertexArrayObject);
}

void GLVertexArray::Unbind() {
    glBindVertexArray(0);
}

void GLVertexArray::clear()
{
    if(!mValid)
        return;

    //delete vbo
    for(U32 i=0; i < mVertexBufferObjects.size(); i++) {
        if(glIsBuffer(mVertexBufferObjects[i]))
            glDeleteBuffers(1, &mVertexBufferObjects[i]);        
    }

    //delete vao
    if(glIsVertexArray(mVertexArrayObject))
        glDeleteVertexArrays(1, &mVertexArrayObject);

}


}
}

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

bool GLVertexArray::Import(U32 count_vertices, const GLVertexArray::GLVertexBufferLayout *layouts, U32 count_layouts)
{
    if(count_layouts == 0 || layouts == NULL) {
        nbLogError("Invalid layout input");
        return false;
    }

    //check layout
    for(U32 i=0; i < count_layouts; i++) {
        U32 attribs_count = layouts[i].attributes.size();
        U32 vertex_packet_size = 0;

        //sum up the dimension of all attributes in this layout
        for(U32 j=0; j < attribs_count; j++) {
            GLVertexAttribute attr = layouts[i].attributes[j];
            vertex_packet_size += attr.mCount;
        }

        U32 rem = layouts[i].buffer.size() % vertex_packet_size;
        if(rem != 0) {
            nbLogError("Layout [%u] does not cover the entire data buffer. rem = %u", i, rem);
            return false;
        }
    }

    //clear
    clear();

    //generate vertex array
    glGenVertexArrays(1, &mVertexArrayObject);

    //1. bind the vao
    glBindVertexArray(mVertexArrayObject);

    //per each layout
    for(U32 i=0; i < count_layouts; i++) {
        U32 attribs_count = layouts[i].attributes.size();
        AttributeLayoutType layoutType = layouts[i].layoutType;

        //compute vertex packet size
        U32 vertex_packet_size = 0;
        for(U32 j=0; j < attribs_count; j++) {
            GLVertexAttribute attr = layouts[i].attributes[j];
            vertex_packet_size += attr.mCount;
        }

        //create the only vertex buffer object
        U32 vbo = 0;
        glGenBuffers(1, &vbo);
        mVertexBufferObjects.push_back(vbo);

        //2. copy data
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * layouts[i].buffer.size(),
                     layouts[i].buffer.data(), GL_STATIC_DRAW);

        //loop over attribs count
        U64 prev_batch_bytes_offset = 0;
        for(U32 j=0; j < attribs_count; j++) {

            GLVertexAttribute attribute = layouts[i].attributes[j];
            U64 byte_offset = 0;
            if(layoutType == altInterleave) {
                byte_offset = attribute.mCount * sizeof(float);
            }
            else if(layoutType == altSequentialBatch) {
                byte_offset = prev_batch_bytes_offset;
            }

            //3. set vertex attrib array
            glEnableVertexAttribArray(attribute.mIndex);
            glVertexAttribPointer(attribute.mIndex, attribute.mCount, GL_FLOAT, GL_FALSE, vertex_packet_size * sizeof(float), (GLvoid*)(byte_offset));

            //accumulate offset
            prev_batch_bytes_offset += count_vertices * attribute.mCount * sizeof(float);
        } //attribs

        //4. unbind buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

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

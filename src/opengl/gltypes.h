#ifndef GLTYPES_H_
#define GLTYPES_H_

namespace nb {
namespace opengl {

//invalid opengl buffer
static const U32 kInvalidGLBuffer = ~0;

//Usage hint for buffer access
enum GLBufferUsage {kStreamDraw = 0x88E0,
					kStreamRead = 0x88E1,
					kStreamCopy = 0x88E2,
					kStaticDraw = 0x88E4,
					kStaticRead = 0x88E5,
					gbuStaticCopy = 0x88E6,
					gbuDynamicDraw = 0x88E8,
					gbuDynamicRead = 0x88E9,
					gbuDynamicCopy = 0x88EA,
};

//Vertex Attribute Types
enum GLVertexAttributeIndex : U32 { kPosition = 0x0,
									kNormal = 0x1,
									kTexture = 0x2,
									kColor = 0x3,
									kWeight = 0x4 };

//Vertex Attributes Layout Type
enum GLVertexAttributeLayoutType { kSeparate, kSequentialBatch, kInterleave };

	//Face Types
enum GLFaceType : U32 {kPoints = 0x0000,
					   kLines = 0x0001,
					   kLineLoop = 0x0002,
					   kLineStrip = 0x0003,
					   kTriangles = 0x0004,
					   kTriangleStrip = 0x0005,
					   kTriangleFan = 0x0006,
					   kQuads = 0x0007,
					   kQuadStrip = 0x0008,
					   kPolygon = 0x0009};

}
}

#endif /* GLTYPES_H_ */

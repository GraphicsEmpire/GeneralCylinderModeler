#include "matrix.h"
#include <stdio.h>
#include <iostream>

using namespace std;

namespace nb {
namespace linalg {


void MtxPrint(const mat4& a)
{
    for(int iRow=0; iRow<4; iRow++)
    {
        for(int iCol=0; iCol<4; iCol++)
        {
            //Print iRow
            printf("%.2f, ", a.GetElement(iRow, iCol));
        }
        printf("\n");
    }
}





}
}

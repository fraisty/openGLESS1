//
// Created by haichao.gao on 20-10-20.
//

#ifndef OPENGLESS1_GLHELPER_H
#define OPENGLESS1_GLHELPER_H

#include <GLES3/gl3.h>

class glHelper {
private:
    static GLuint LoadShader(GLenum type, const char *shaderSrc);

public:
    static GLuint CreateProgram(const char *, const char *);





};


#endif //OPENGLESS1_GLHELPER_H

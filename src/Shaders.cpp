#include "Shaders.h"
std::string shaders::grid_vs;
std::string shaders::grid_gs;
std::string shaders::grid_fs;

void shaders::updateGridShader(std::string* code)
{
//    editCode(code);

    shaders::grid_vs = std::string("") +
                                "#version 330 \n" +
                                "layout (location = 0) in vec2 pos;" +
                                "void main() " +
                                "{ gl_Position = vec4(pos.x, pos.y, 0 , 1);}";

    shaders::grid_gs = std::string("") +
                                "#version 330 \n" +
                                "layout (lines) in; " +
                                "layout (line_strip, max_vertices=100) out; " +
                                "uniform mat4 ortho; " +
                                "uniform float t; " +
                                "uniform float mag;" +
                                "out vec2 outPos;" +
                                "vec2 multiply(vec2, vec2);" +
                                "vec2 divide(vec2, vec2);" +
                                "void main() " +
                                "{" +
                                "   vec2 start = (gl_in[0].gl_Position).xy; " +
                                "   vec2 end = (gl_in[1].gl_Position).xy; " +
                                "   float delta = 1.0f/(2*mag-1); " +
                                "   for(float i=0; i<=1.0f; i+=delta)" +
                                "   { " +
                                "       vec2 z = (1-i)*start + (i)*end;" +
                                "       outPos = z; " +
                                *code +
                                "       vec2 start = outPos, finish = z;" +
                                "       float relativeY = finish.y*start.x - finish.x*start.y;" +
                                "       float rot = relativeY > 0 ? 1 : -1;" +
                                "       vec2 interpolatedZ;" +
                                "       if( relativeY < 0.001 && relativeY > -0.001) " +
                             //   "if(true)"+
                                "           interpolatedZ = (1-t)*start + t*finish;" +
                                "       else{" +
                                "           vec2 vStart = vec2(-1*rot*start.y, rot*start.x);  vec2 vFinish = vec2(-1*rot*finish.y, rot*finish.x);" +
                                "           float radii = length(vStart)/length(vFinish);" +
                                "           normalize(vStart); normalize(vFinish);" +
                                "           vFinish = radii * vFinish;" +
                                "           vec2 A = vFinish + vStart + 2*start - 2*finish; " +
                                "           vec2 B = 3*finish - 3*start - 2*vStart - vFinish;" +
                                "           interpolatedZ = A*t*t*t + B*t*t + vStart*t + start;"+
                                "       }" +
                                "       gl_Position = ortho*vec4(interpolatedZ.x, interpolatedZ.y, 0, 1); " +
                                "       EmitVertex(); " +
                                "   }" +
                                "   EndPrimitive();" +
                                "} " +
                                "vec2 multiply(vec2 a, vec2 b) " +
                                "{" +
                                "   return vec2( a.x*b.x - a.y*b.y , a.x*b.y + a.y*b.x);  " +
                                "}" +
                                "vec2 divide(vec2 divident, vec2 divisor)" +
                                "{ " +
                                "   float r2 = divisor.x*divisor.x + divisor.y*divisor.y;  " +
                                "   vec2 divisorConjugate = vec2(divisor.x, -1*divisor.y); " +
                                "   divisorConjugate = divisorConjugate/r2; " +
                                "   vec2 ans = multiply(divident , divisorConjugate) ; " +
                                "   return ans; " +
                                "}" ;

    shaders::grid_fs = std::string("") +
                                "#version 330 \n" +
                                "out vec4 fragColor;" +
                                "in vec2 outPos; " +
                                "void main() " +
                                "{  " +
                                "  if( (outPos.x > -0.01f && outPos.x < 0.01f) || (outPos.y > -0.01f && outPos.y < 0.01f) ) " +
                                "   fragColor = vec4(0.8f,0.7f,0.2f,1.0f); " +
                                "  else " +
                                "    fragColor = vec4(0.1f,0.7f,0.8f,1); " +
                                "} " ;

}


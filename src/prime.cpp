#include "Engine.h"

int main(int argc, char** argv)
{

    char* title = (char*)"Argand Plane";
    std::string code;
    if(argc > 1)
        code += argv[1];
    Engine engine(512,512,title,code);
    return 0;
}

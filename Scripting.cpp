//
// Created by Ben Redmond on 11/2/18.
//

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

int compileFile(std::string file) {
    std::string cmd = "../compile.sh " + file + ".cpp";
    const char *cstr = cmd.c_str();
    return system(cstr);
}

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

int main() {
//    std::cout << compileFile("main");

    std::string res = exec("../checker-279/libexec/c++-analyzer ../main.cpp 2>&1");
    std::cout << res;

//    std::ifstream infile("../main.cpp");
//    std::string str;
//    while (std::getline(infile, str))
//    {
//        std::istringstream iss(str);
//        std::string str2;
//        std::cout << str << std::endl;
//    }

    return 0;
}


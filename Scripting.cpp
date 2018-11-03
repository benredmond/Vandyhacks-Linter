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

std::string exec(const char* cmd) {
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
    std::string cmd = "cppcheck --enable=all --template=\"{file}:{line}: {severity}: {message}\" --suppress=missingIncludeSystem ../main.cpp 2>&1";
    std::string res = exec(cmd.c_str());
    std::istringstream f(res);
    std::string line;

    while (std::getline(f, line)) {
        int counter = 0;
        while (line.length() != 0 && line.find(":") != std::string::npos) {
            std::string first = line.substr(0, line.find(":"));
            line.erase(0, line.find(":") + 1);
//            if (counter == 2)
                std::cout << first << std::endl;
            ++counter;
        }
//        std::cout << line << std::endl;
    }

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


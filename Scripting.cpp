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

size_t index (std::string line){
    size_t index = 0;
    while (line[index] != ':'){
        index++;
//        std::cout << line[index] << std::endl;
    }
    return index;
}

int main() {
    const std::string FILENAME = "main";
    std::cout << "EXIT CODE: " << compileFile(FILENAME) << std::endl;

    std::string outputCmd = "../compile.sh " + FILENAME + ".cpp";
    std::string output = exec(outputCmd.c_str());
    std::cout << "OUTPUT: " << output;

    std::string linterCmd = "cppcheck --enable=all --template=\"{file}:{line}: {severity}: {message}\" --suppress=missingIncludeSystem ../main.cpp 2>&1";
    std::string linterRes = exec(linterCmd.c_str());
    std::istringstream f(linterRes);
    std::string line;

    while (std::getline(f, line)) {
//        std::cout << "index of : " << index(line) << std::endl;
        std::cout << line << std::endl;
    }

    return 0;
}


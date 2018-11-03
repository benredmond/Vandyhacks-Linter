//
// Created by Ben Redmond on 11/2/18.
//

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <map>

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

void parse (std::map<size_t, std::string> &map1, std::map<std::string, size_t> &map2,std::string line){
 size_t firstColonIndex = 0;
 size_t secondColonIndex = 0;
 size_t thirdColonIndex = 0;
 size_t colonCount = 0;
 size_t index = 0;
 while (index != line.length() - 1){
     if (line[index] == ':'){
         colonCount++;
         if (colonCount == 1){
             firstColonIndex = index;
         }
         else if (colonCount == 2){
             secondColonIndex = index;
         }
         else if (colonCount == 3){
             thirdColonIndex = index;
         }
     }
     index++;
 }
//    std::cout << "first colon index = " << firstColonIndex << std::endl;
//    std::cout << "second colon index = " << secondColonIndex << std::endl;
//    std::cout << "third colon index = " << thirdColonIndex << std::endl;

    //time to map things
    int lineNum1 = stoi(line.substr(firstColonIndex + 1, (secondColonIndex - (firstColonIndex + 1))));
    size_t lineNum2 = (size_t) lineNum1;
    //std::cout << "line number: " << lineNum2 << std::endl;
    std::string messageType = line.substr(secondColonIndex + 2, (thirdColonIndex - (secondColonIndex + 2)));
    //std::cout << "message type: " << messageType << std::endl;
    std::string message = line.substr(thirdColonIndex + 2, line.length() - 1);
    //std::cout << "message: " << message << std::endl;

}


int main() {
//    std::cout << compileFile("main");
    std::string cmd = "cppcheck --enable=all --template=\"{file}:{line}: {severity}: {message}\" --suppress=missingIncludeSystem ../main.cpp 2>&1";
    std::string res = exec(cmd.c_str());
    std::istringstream f(res);
    std::string line;
    std::map<size_t, std::string> lineAndDescription;
    std::map<std::string, size_t> typeAndCount;
    size_t errorCount = 0;
    while (std::getline(f, line)) {
        std::cout << line << std::endl;
        if (errorCount != 0){
            parse(lineAndDescription, typeAndCount, line);
        }
        errorCount++;
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


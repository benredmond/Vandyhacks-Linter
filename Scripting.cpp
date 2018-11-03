#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

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

int main(int argc, char *argv[]) {
    std::string linterCmd = "cppcheck --enable=all --template=\"{file}:{line}: {severity}: {message}\" "
            "--suppress=missingIncludeSystem ./cpp/";
    linterCmd.append(argv[1]);
    linterCmd.append(".cpp 2>&1");
    std::string linterRes = exec(linterCmd.c_str());
    std::istringstream f(linterRes);
    std::string line;

    while (std::getline(f, line)) {
//        std::cout << "index of : " << index(line) << std::endl;
        std::cout << line << std::endl;
    }

    return 0;
}


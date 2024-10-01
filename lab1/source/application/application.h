#include <iostream>
#include <unordered_map>

#include "../coder/coder.h"

class Application {
private:
    Coder coder;
    int length;
    char** args;
    std::string version = "1.0.0";

    void print(std::string value);

    void decode(std::string input, std::string output, bool showCode);

    void code(std::string input, std::string output, bool showCode);

    void argumentParser(void (Application::*function) (std::string input, std::string output, bool showCode));

    void help();

    void help(std::string const & functionName);

    void parse();
public:
    Application(int numberOfArguments, char** arguments);
};
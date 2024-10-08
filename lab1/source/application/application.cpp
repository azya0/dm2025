#include "application.h"

void Application::print(std::string value) {
    std::cout << value;
}

void Application::decode(std::string input, std::string output, bool showCode) {
    coder.decode(input, output, showCode);
}

void Application::code(std::string input, std::string output, bool showCode) {
    coder.code(input, output, showCode);
}

void Application::argumentParser(void (Application::*function)(std::string input, std::string output, bool showCode)) {
    std::string inputFile;
    std::string outputFile;
    bool showCode = false;

    for (int index = 2; index <= length; index++) {
        std::string arg(args[index]);

        if (arg == "-s") {
            if (showCode) {
                throw std::runtime_error("error: -s already was\nuse \"[-h | --help] code\"");
            }

            showCode = true;
        } else if (arg == "-i" || arg == "-o") {
            if ((index + 1) > length) {
                throw std::runtime_error("error: few arguments\nuse \"[-h | --help] code\"");
            }

            index++;

            if (arg == "-i") {
                inputFile = std::string(args[index]);
            } else {
                outputFile = std::string(args[index]);
            }
        } else {
            throw std::runtime_error("error: unknown argument " + arg + "\nuse \"[-h | --help] code\"");
        }
    }

    if (inputFile.empty()) {
        throw std::runtime_error("error: miss input file\nuse \"[-h | --help] code\"");
    } else if (outputFile.empty()) {
        throw std::runtime_error("error: miss output file\nuse \"[-h | --help] code\"");
    }

    (this->*function)(inputFile, outputFile, showCode);
}

void Application::help() {
    print("[-v | --version]\t\tget program version\n");
    print("[-h | --help]\t\t\tget subcommands list\n");
    print("[-h | --help] <subcommand name>\tget subcommand info\n");
    print("\nSubcommand list:\n\n");
    print("\tcode\t\t Code file\n");
    print("\tdecode\t\t Decode file");
}

void Application::help(std::string const & functionName) {
    if (functionName == "-v" || functionName == "-v") {
        print("[-v | --version] get program version");
    } else if (functionName == "--help" || functionName == "-h") {
        print("[-h | --help]\t\t\tget subcommands list\n");
        print("[-h | --help] <subcommand name>\tget subcommand info\n");
        print("\nYou're just kidding, right?");
    } else if (functionName == "code") {
        print("[code] : the command creates a file encoded by the Fano algorithm\n");
        print("usage: code -i <input file name> -o <output file name>\n");
        print("\tuse -s flag to show codes");
    } else if (functionName == "decode") {
        print("[decode] : the command creates a file decode by the Fano algorithm\n");
        print("\nWARNING : Decoding will work correctly\nONLY if the file was previously\ncreated using the [code]\nsubcommand and was not modified\nbefore the [decode] subcommand.\nOtherwise, the author of the program\nis not responsible for the result of calling this subcommand.\n\n");
        print("usage: decode -i <input file name> -o <output file name>");
        print("\tuse -s flag to show codes");
    } else {
        throw std::runtime_error("miss \"" + functionName + "\" subcommand");
    }
}

void Application::parse() {
    if (length == 0) {
        print("use \"--help\" to get list of available subcommands");
        return;
    }

    std::string subcommand(args[1]);

    if (subcommand == "-h" || subcommand == "--help") {
        if (length == 1) {
            help();
        } else if (length == 2) {
            help(std::string(args[2]));
        } else {
            throw std::runtime_error("error: unknown arguments\nuse \"[-h | --help] --help\"");
        }
    } else if (subcommand == "-v" || subcommand == "--version") {
        if (length == 1) {
            print(version);
        } else {
            throw std::runtime_error("error: unknown arguments\nuse \"[-h | --help] --version\"");
        }
    } else if (subcommand == "code") {
        argumentParser(&Application::code);
    } else if (subcommand == "decode") {
        argumentParser(&Application::decode);
    } else {
        throw std::runtime_error("error: unknown subcommand\nuse \"[-h | --help]\" to get subcommands list" );
    }
}

Application::Application(int numberOfArguments, char **arguments) {
    length = numberOfArguments - 1;
    args = arguments;

    parse();
}
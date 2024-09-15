#include "lab1.h"

namespace lab1 {
    const char* parse(const char* name, const char* jsonStr) {
        std::string resStr = parse(std::string(name), std::string(jsonStr));
        char* res = new char[resStr.length() + 1] {};
        std::copy(resStr.begin(), resStr.end() + 1, res);
        return res;
    }

    std::string parse(const std::string& name, const std::string& jsonStr) {
        std::string str = jsonStr;
        str.erase(remove_if(str.begin(), str.end(), isspace), str.end());

        if (!str.starts_with('{'))
            throw std::runtime_error("Error: bad json input, must start with \'{\'");

        std::vector<std::string> subStrings;
        for (std::string::iterator i = str.begin(); i != str.end(); i++)
            if (*i == '{' || *i == ':' || *i == ',')
                subStrings.push_back("");
            else if (*i != '}')
                subStrings.back().push_back(*i);

        std::string res = "struct " + name + " { ";

        if (subStrings.size() == 1 && subStrings[0] == "")
            subStrings.pop_back();

        for (std::vector<std::string>::iterator i = subStrings.begin(); i != subStrings.end(); i++) {
            if (getType(*i) == jsonString) {
                std::string varName = (*i).substr(1, (*i).length() - 2);
                i++;

                switch (getType(*i)) {
                case jsonVoid:
                    res += "\n\tvoid* ";
                    break;
                case jsonBool:
                    res += "\n\tbool ";
                    break;
                case jsonString:
                    res += "\n\tchar* ";
                    break;
                case jsonDouble:
                    res += "\n\tdouble ";
                    break;
                case jsonLong:
                    res += "\n\tlong ";
                    break;
                }

                res += varName + ";";
            }
            else
                throw std::runtime_error("bad json input");
        }

        res = res.substr(0, res.length() - 1) + "\n};";

        return res;
    }

    jsonType getType(std::string& str) {
        if (str == "null")
            return jsonVoid;
        if (str == "true" || str == "false")
            return jsonBool;
        if (str.starts_with('\"') && str.ends_with('\"'))
            return jsonString;
        if (std::all_of(str.begin(), str.end(), isdigit))
            return jsonLong;
        if (isDouble(str))
            return jsonDouble;
        else
            throw std::runtime_error("bad json input");
    }

    bool isDouble(std::string& str) {
        for (std::string::iterator i = str.begin(); i != str.end(); i++)
            if (!isdigit(*i) && *i != '.')
                return false;
        return true;
    }

    void loop() {
        std::string ovld{};
        bool inputLoop = true;
        while (inputLoop) {
            std::cout << "Which overload to use:\n1 - std::string\n2 - const char*\n0 - exit" << std::endl;
            std::cin >> ovld;
            if (ovld == "0")
                inputLoop = false;
            else if (ovld == "1" || ovld == "2") {
                std::string name;
                std::cout << "Enter struct name: " << std::flush;
                std::cin >> name;

                std::string jsonStr;
                std::string str{};
                std::cout << "Enter JSON-string(ends with \'}\')" << std::endl;
                while (std::find(str.begin(), str.end(), '}') == str.end()) {
                    str.erase(str.begin(), str.end());
                    std::cin >> str;
                    jsonStr += str;
                }

                if (ovld == "1") {
                    std::string res = parse(name, jsonStr);
                    std::cout << res << std::endl;
                }
                else {
                    char* nameChar = new char[name.length() + 1];
                    std::copy(name.begin(), name.end() + 1, nameChar);
                    char* strChar = new char[jsonStr.length() + 1];
                    std::copy(jsonStr.begin(), jsonStr.end() + 1, strChar);
                    const char* res;
                    try {
                        res = parse(nameChar, strChar);
                    }
                    catch (const std::exception& e) {
                        delete[] nameChar;
                        delete[] strChar;
                        throw;
                    }
                    std::cout << res << std::endl;
                    delete[] nameChar;
                    delete[] strChar;
                    delete[] res;
                }
            }
            else
                std::cout << "Bad input" << std::endl;
        }

    }
}
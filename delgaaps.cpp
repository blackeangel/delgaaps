//standart C++17
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

vector<string> readlines(string file)
{
    vector<string> lines;
    ifstream open_file(file, ios::in);
    if (!open_file.is_open()) {
        cout << file << " not found" << endl;
        exit(2);
    }
    for (std::string line; std::getline(open_file, line); )
        lines.push_back(line);
    open_file.close();
    return lines;
}

int main(int argc, char* argv[])
{

    cout << "\nDesigned by blackeangel (blackeangel@mail.ru) for UKA tools\n" << endl;
    if (argc != 4) {
        cout << "Usage:" << endl;
        cout << "     delgaaps <folder> <name_image> <file_list>" << endl;
        cout << "Where:" << endl;
        cout << "<folder> - path to the folder where the image was unpacked" << endl;
        cout << "<name_image> - image name without extension (.img)" << endl;
        cout << "<file_list> - a file with a list of regular expressions to remove gaaps and more" << endl;
        cout << "For example:" << endl;
        cout << "delgaaps \"/data/local/UnpackerSystem\" \"system\" \"/storage/emulated/0/gappslist.txt\"" << endl;
        exit(1);
    }

    //argv to string -->
    vector<string> allArgs;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            allArgs.push_back(argv[i]);
        }
    }
    //argv to string <---
    string config_path(allArgs.at(0) + "/config");
    string config_file = config_path + "/" + allArgs.at(1) + "/" + allArgs.at(1) + "_fs_config";
    string name_img_path = allArgs.at(0) + "/" + allArgs.at(1);
    string gaapslist_file(allArgs.at(2));
    vector<string> gaapslist = readlines(gaapslist_file);
    vector<string> name_img = readlines(config_file);
    vector<string> name_img_clone = name_img;
    regex reg(" \\d{1,4} \\d{1,4} \\d{1,4}( .*)?");
    for (int i = 0; i < name_img_clone.size(); i++) {
        name_img_clone.at(i) = regex_replace(name_img_clone.at(i), reg, "");
    }
    for (int i = 0; i < name_img_clone.size(); i++) {
        for (int j = 0; j < gaapslist.size(); j++) {
            regex regtmp;
            try {
                regex r(gaapslist.at(j));
                regtmp = std::move(r);
            }
            catch (const std::regex_error& e) {
                std::cout << "Bad Regular Expression: " << "\"" << gaapslist.at(j) << "\", " << e.what() << '\n';
                if (e.code() == std::regex_constants::error_brack) {
                    std::cout << "The code was error_brack\n";
                }
                exit(-1);
            }
            smatch sm;
            if (regex_search(name_img_clone.at(i), sm, regtmp)) {
                std::filesystem::path path = allArgs.at(0) + "/" + name_img_clone.at(i);
                if (std::filesystem::exists(path)) {
                    std::filesystem::remove_all(path);
                    cout << "Deleted: " << path << endl;
                }
                name_img.at(i) = "";
                break;
            }
        }
    }
    //delete empty elements from vector -->
    auto isEmptyOrBlank = [](const std::string& s) {
        return s.find_first_not_of("") == std::string::npos;
    };
    name_img.erase(std::remove_if(name_img.begin(), name_img.end(), isEmptyOrBlank), name_img.end());
    //delete empty elements from vector <--

    //write vector to file -->
    std::fstream config(config_file, ios::out);
    std::copy(name_img.begin(), name_img.end(), std::ostream_iterator<string>(config, "\n"));
    //write vector to file <--

    return 0;
}

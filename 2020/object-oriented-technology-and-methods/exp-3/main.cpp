#include "copy.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        Copy::HelpInfo();
        return 0;
    } else {
        Copy copy = Copy();
        bool loaded_source_file = false;
        bool loaded_destination_file = false;
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                if (i + 1 < argc) {
                    int flag = copy.LoadValidOptions(argv[i], argv[i + 1]);
                    if (flag == -1) {
                        break;
                    } else if (flag == 0) {
                        continue;
                    } else if (flag == 1) {
                        i++;
                        continue;
                    }
                } else {
                    copy.LoadValidOptions(argv[i], argv[i]);
                }
            } else {
                if (copy.get_should_exit()) {
                    return 0;
                }
                if (!loaded_source_file) {
                    copy.set_source_file(string(argv[i]));
                    loaded_source_file = true;
                } else if (!loaded_destination_file) {
                    copy.set_destination_file(string(argv[i]));
                    loaded_destination_file = true;
                } else {
                    copy.LoadInvalidOption(argv[i]);
                    return 0;
                }
            }
        }
        if (copy.get_should_exit()) {
            return 0;
        } else {
            copy.CopyFile();
            return 0;
        }
    }
}
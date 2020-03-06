#include "copy.h"

Copy::Copy() {
    this->source_file = string();
    this->destination_file = string();
    this->append_mode = false;
    this->should_exit = false;
    this->lines = -1;
}

void Copy::set_source_file(const string &source_file_) {
    regex match(R"(^[a-zA-Z]:([\\/][^\s\\/:*?<>"|][^\\/:*?<>"|]*)*([/\\])?$)");
    if (regex_match(source_file_, match)) {
        this->source_file = source_file_;
    } else {
        Copy::ErrorInfo(100);
        cout << "  Error occurred near input \"" + source_file_ + "\".\n" << endl;
        this->should_exit = true;
    }
}

void Copy::set_destination_file(const string &destination_file_) {
    regex match(R"(^[a-zA-Z]:([\\/][^\s\\/:*?<>"|][^\\/:*?<>"|]*)*([/\\])?$)");
    if (regex_match(destination_file_, match)) {
        this->destination_file = destination_file_;
    } else {
        Copy::ErrorInfo(100);
        cout << "  Error occurred near input \"" + destination_file_ + "\".\n" << endl;
        this->should_exit = true;
    }
}

bool Copy::get_should_exit() {
    return this->should_exit;
}

void Copy::HelpInfo() {
    cout << " ________  ________  ________  ___    ___ \n"
            "|\\   ____\\|\\   __  \\|\\   __  \\|\\  \\  /  /|\n"
            "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\/  / /\n"
            " \\ \\  \\    \\ \\  \\\\\\  \\ \\   ____\\ \\    / / \n"
            "  \\ \\  \\____\\ \\  \\\\\\  \\ \\  \\___|\\/  /  /  \n"
            "   \\ \\_______\\ \\_______\\ \\__\\ __/  / /    \n"
            "    \\|_______|\\|_______|\\|__||\\___/ /     \n"
            "                             \\|___|/        v0.1 by ZSB 2020.3.5\n"
            "https://github.com/Overloadlightning/BIT/tree/master/2020/object-oriented-technology-and-methods/exp-3\n\n"
            "Copy a file content to another file.\n\n"
            "Usage:  Copy.exe [OPTIONS] SOURCE_FILE[DESTINATION_FILE]\n\n"
            "FILES:\n"
            "  Windows: Please input absolute pathname like \"C:\\User\\MyFile\\Example.file\"\n\n"
            "Options:\n"
            "  -a, --append       change the copy mode to append mode.\n"
            "                     if not set, the copy mode is write mode.\n"
            "  -l, --lines NUM    copy the first NUM lines instead of whole file\n"
            "      --help         display this help and exit\n" << endl;
}

void Copy::ErrorInfo(int error_code) {
    switch (error_code) {
        case 100: {
            cout << "\n!ERROR!\n"
                    "  Invalid input arguments. (ERROR CODE 100)\n"
                    "  Please check your input or run with \"--help\" option.\n" << endl;
            break;
        }
        case 101: {
            cout << "\n!ERROR!\n"
                    "  No such options for Copy. (ERROR CODE 101)\n"
                    "  Please check your input or run with \"--help\" option.\n" << endl;
            break;
        }
        case 102: {
            cout << "\n!ERROR!\n"
                    "  Invalid value for option \"--lines\". (ERROR CODE 102)\n"
                    "  Please check your input or run with \"--help\" option.\n" << endl;
            break;
        }
        case 103: {
            cout << "\n!ERROR!\n"
                    "  Too many arguments. (ERROR CODE 103)\n"
                    "  Please check your input or run with \"--help\" option.\n" << endl;
            break;
        }
        case 200: {
            cout << "\n!ERROR!\n"
                    "  No such source file or can not open it. (ERROR CODE 200)\n"
                    "  Please check your input or run with \"--help\" option.\n" << endl;
            break;
        }
        case 201: {
            cout << "\n!ERROR!\n"
                    "  No such destination file or can not open it. (ERROR CODE 201)\n"
                    "  Please check your input or run with \"--help\" option.\n" << endl;
            break;
        }
        default: {
            cout << "\n!ERROR!\n"
                    "  Undetermined error. (ERROR CODE xxx)\n"
                    "  Please check your input or run with \"--help\" option.\n" << endl;
            break;
        }
    }
}

int Copy::LoadValidOptions(const char *option, const char *option_value) {
    if (strcmp(option, "-a") == 0 || strcmp(option, "--append") == 0) {
        this->append_mode = true;
        return 0;
    } else if (strcmp(option, "-l") == 0 || strcmp(option, "--lines") == 0) {
        int lines_ = 0, value_len = strlen(option_value);
        for (int i = 0; i < value_len; i++)
            if (option_value[i] >= '0' && option_value[i] <= '9') {
                lines_ = lines_ * 10 + (option_value[i] - '0');
            } else {
                Copy::ErrorInfo(102);
                cout << "  Error occurred near input \"" + string(option_value) + "\".\n" << endl;
                this->should_exit = true;
                return -1;
            }
        this->lines = lines_;
        return 1;
    } else if (strcmp(option, "--help") == 0) {
        Copy::HelpInfo();
        this->should_exit = true;
        return 0;
    } else {
        Copy::ErrorInfo(101);
        cout << "  Error occurred near input \"" + string(option) + "\".\n" << endl;
        this->should_exit = true;
        return -1;
    }
}

void Copy::LoadInvalidOption(const char *option) {
    Copy::ErrorInfo(103);
    cout << "  Error occurred near input \"" + string(option) + "\".\n" << endl;
    this->should_exit = true;
}

bool Copy::CopyFile() {
    ifstream infile(this->source_file);
    if (!infile.good() || !infile.is_open()) {
        Copy::ErrorInfo(200);
        cout << "  Error occurred near input \"" + this->source_file + "\".\n" << endl;
        return false;
    }
    ofstream outfile;
    if (this->append_mode) {
        outfile.open(this->destination_file, ios::app);
        if (!outfile.good() || !outfile.is_open()) {
            Copy::ErrorInfo(201);
            cout << "  Error occurred near input \"" + this->destination_file + "\".\n" << endl;
            return false;
        }
        cout << "\n  Copying file:\n    " +
                source_file +
                "\n  To file:\n    " +
                destination_file +
                "\n  In append mode...\n" << endl;
    } else {
        if (access(this->destination_file.c_str(), F_OK) == 0) {
            cout << "\n  File: " + this->destination_file + " will be overwritten.\n\n"
                                                            "Do you want to continue? [Y/n]: ";
            string confirm;
            cin >> confirm;
            if (confirm != "Y") {
                cout << "\n  Copy abort.\n" << endl;
                return false;
            }
        } else {
            cout << "\n  File: " + this->destination_file + " does not exists. Auto created." << endl;
        }
        outfile.open(this->destination_file, ios::trunc);
        if (!outfile.good() || !outfile.is_open()) {
            Copy::ErrorInfo(201);
            cout << "  Error occurred near input \"" + this->destination_file + "\".\n" << endl;
            return false;
        }
        cout << "\n  Copying file:\n    " +
                source_file +
                "\n  To file:\n    " +
                destination_file +
                "\n  In write mode...\n" << endl;
    }
    string temp;
    if (this->lines == -1) {
        while (getline(infile, temp)) {
            outfile << temp;
            outfile << endl;
        }
    } else {
        int line = 0;
        while (line < this->lines && getline(infile, temp)) {
            line++;
            outfile << temp;
            outfile << endl;
        }
    }
    infile.close();
    outfile.close();
    cout << "  Copy succeeded!\n" << endl;
    return true;
}

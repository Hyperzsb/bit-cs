#ifndef EXP_3_COPY_H
#define EXP_3_COPY_H

#include <iostream>
#include <fstream>
#include <io.h>
#include <string>
#include <cstring>
#include <utility>
#include <regex>

using namespace std;

class Copy {

private:
    /**
     * @description Path string of source file.
     */
    string source_file;
    /**
     * @description Path string of destination file.
     */
    string destination_file;
    /**
     * @description Use append copy mode or not
     */
    bool append_mode;
    /**
     * @description If the program should to exit(when argument is invalid, "--help" option is used, etc).
     */
    bool should_exit;
    /**
     * @desscription Determine how many lines will be copied when "--lines" option is used.
     */
    int lines;

public:
    /**
     * @description Constructor of Copy class.
     */
    Copy();

    /**
     * @description Set path string of source file.
     * @param source_file_ Path string of source file.
     */
    void set_source_file(const string &source_file_);

    /**
     * @description Set path string of destination file.
     * @param destination_file_ Path string of destination file.
     */
    void set_destination_file(const string &destination_file_);

    /**
     * @description Decide whether to exit or not.
     */
    bool get_should_exit();

    /**
     * @description Display the help information.
     */
    static void HelpInfo();

    /**
     * @description Display the error information via error code.
     * @param error_code Error code of the error.
     */
    static void ErrorInfo(int error_code);

    /**
     * @description Load and check the option supplied is valid or not.
     *              If valid, set the corresponding property of the instance.
     * @param option Option name.
     * @param option_value Option value.
     * @return How many arguments should be skipped
     */
    int LoadValidOptions(const char *option, const char *option_value);

    /**
     * @description Load and check the invalid option.
     * @param option Option name.
     */
    void LoadInvalidOption(const char *option);

    /**
     * @description Execute the copy operation.
     * @return Whether the copy operation is successful or not.
     */
    bool CopyFile();
};


#endif //EXP_3_COPY_H

#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

#include <memory>
#include <vector>
#include <string>

#include "../logger/BaseLogger.hpp"
#include "../logger/ConsoleLogger.hpp"
#include "../networks/LinuxSockets.hpp"
#include "../networks/SocketInterfaces.hpp"
#include "../networks/Server.hpp"
#include "../networks/Client.hpp"
#include "../networks/FileInfo.hpp"

enum Command {
    SEND,
    RECEIVE,
    HELP,
    NOT_DEFINED,
};

#define TEXT_SEND_COMMAND "send"
#define TEXT_RECEIVE_COMMAND "receive"
#define TEXT_HELP_COMMAND "--help"

enum ExitCode {
    SUCCESS = 0,
    ERROR = 1,
};

#define MANUAL \
"MANUAL:\n" \
"\n"\
"usage: ./app.exe [option] [progs-and-agrs]\n" \
"\n" \
"OPTIONS:\n"\
"\n"\
"\tsend <receiver-ip> <receiver-port> [file1] ... [fileN]\n"\
"\tSend file1, ..., fileN to the specified receiver.\n"\
"\n"\
"\treceive <port> <number-of-files>\n"\
"\tReceive the indicated number of files from the sender.\n"\
"\n"\
"\t--help\n"\
"\tShow manual."


class Console {
private:
    std::vector<std::string> argv;
    std::shared_ptr<BaseLogger> logger;

    static Command define_command(const std::string &text_command);
    
    ExitCode send();
    ExitCode _send();

    ExitCode receive();
    ExitCode _receive();

    ExitCode help() const;

public:
    Console(int argc, char **_argv, std::shared_ptr<BaseLogger> &logger);
    ExitCode run();
};

#endif
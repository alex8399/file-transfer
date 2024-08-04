#include "Console.hpp"

Command Console::define_command(const std::string &text_command)
{
    Command command = Command::NOT_DEFINED;

    if (text_command.compare(TEXT_SEND_COMMAND) == 0)
    {
        command = Command::SEND;
    }
    else if (text_command.compare(TEXT_RECEIVE_COMMAND) == 0)
    {
        command = Command::RECEIVE;
    }
    else if (text_command.compare(TEXT_HELP_COMMAND) == 0)
    {
        command = Command::HELP;
    }

    return command;
}

Console::Console(int argc, char **argv, std::shared_ptr<BaseLogger> &logger)
{
    this->logger = logger;

    this->argv.resize(argc);

    for (int ind = 0; ind != argc; ++ind)
    {
        this->argv[ind] = argv[ind];
    }
};

ExitCode Console::run()
{
    ExitCode exit_code = ExitCode::SUCCESS;
    Command command = Command::NOT_DEFINED;

    if (this->argv.size() > 0)
    {
        command = Console::define_command(this->argv[1]);
    }

    switch (command)
    {
    case Command::SEND:
        this->logger->log("Command 'send' is set.");
        exit_code = this->send();
        break;
    case Command::RECEIVE:
        this->logger->log("Command 'receive' is set.");
        exit_code = this->receive();
        break;
    case Command::HELP:
        this->logger->log("Command 'help' is set.");
        exit_code = this->help();
        break;
    default:
        logger->log("Command is not defined.");
        logger->log("Use --help for more information.");
        exit_code = ExitCode::ERROR;
        break;
    }

    return exit_code;
}

ExitCode Console::send()
{
    ExitCode exit_code = ExitCode::SUCCESS;

    try
    {
        exit_code = this->_send();
    }
    catch (const std::exception &err)
    {
        this->logger->log("ERROR: " + std::string(err.what()));
        this->logger->log("File sender has stopped working.");
        exit_code = ExitCode::ERROR;
    }

    return exit_code;
}

ExitCode Console::_send()
{
    ExitCode exit_code = ExitCode::SUCCESS;

    this->logger->draw_line();

    if (this->argv.size() < 4)
    {
        throw std::invalid_argument("IP address of server or port were not indicated.");
    }

    LinuxClientSocketFactory client_socket_factory(this->argv[2], std::stoi(this->argv[3]));
    Client client(client_socket_factory);

    this->logger->log("File sender is wainting response from file reciever.");
    client.establish_connection();
    this->logger->log("Connection is established.");

    this->logger->log("The file transfer has started.");
    this->logger->draw_line();

    for (size_t ind = 4; ind != this->argv.size(); ++ind)
    {
        this->logger->log("The transfer of file " + this->argv[ind] + " has started.");
        std::shared_ptr<FileInfo> file = client.send_file(this->argv[ind]);
        this->logger->log("The transfer of file " + file->name + " has finished."
                                                                 " The size of " +
                          file->name + " is " + std::to_string(file->size) + " bites.");
        this->logger->draw_line();
    }

    this->logger->log("The file transfer has finished.");
    client.close_connection();
    this->logger->log("Connection was closed.");

    return exit_code;
}

ExitCode Console::receive()
{
    ExitCode exit_code = ExitCode::SUCCESS;

    try
    {
        exit_code = this->_receive();
    }
    catch (const std::exception &err)
    {
        this->logger->log("ERROR: " + std::string(err.what()));
        this->logger->log("File receiver has stopped working.");
        exit_code = ExitCode::ERROR;
    }

    return exit_code;
}

ExitCode Console::_receive()
{
    ExitCode exit_code = ExitCode::SUCCESS;

    this->logger->draw_line();

    if (this->argv.size() < 4)
    {
        throw std::invalid_argument("Port and number of files were not indicated.");
    }

    LinuxServerSocketFactory server_socket_factory(std::stoi(this->argv[2]));
    Server server(server_socket_factory);

    this->logger->log("File receiver is waiting for response from file sender.");
    server.establish_connection();
    this->logger->log("Connection is established.");

    const size_t file_number = std::stoi(this->argv[3]);
    size_t file_counter = 0;
    size_t file_ind = 0;

    this->logger->log("The file downloading has started.");
    this->logger->draw_line();

    while (file_counter < file_number)
    {
        file_ind = file_counter + 1;

        this->logger->log("The downloading of " + std::to_string(file_ind) + " file has started.");
        std::shared_ptr<FileInfo> file = server.recv_file();
        this->logger->log("The downloading of file " + file->name + " has finished."
                                                                    " The size of " +
                          file->name + " is " + std::to_string(file->size) + " bites.");

        file_counter += 1;
        this->logger->draw_line();
    }

    this->logger->log("The file downloading has finished.");
    server.close_connection();
    this->logger->log("Connection was closed.");

    return exit_code;
}

ExitCode Console::help() const
{
    ExitCode exit_code = ExitCode::SUCCESS;
    this->logger->draw_line();
    this->logger->log(MANUAL);
    this->logger->draw_line();
    return exit_code;
}
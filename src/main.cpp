#include "./console/Console.hpp"
#include "./logger/ConsoleLogger.hpp"
#include "./logger/BaseLogger.hpp"
#include <memory>

int main(int argc, char* argv[]) {
    std::shared_ptr<BaseLogger> logger = std::make_shared<ConsoleLogger>(
        ConsoleLogger(std::cout));
    Console console(argc, argv, logger);
    return console.run();
}
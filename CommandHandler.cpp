//#include "CommandHandler.h"
//#include <unordered_set>
//#include <iostream>


//CommandHandler::CommandHandler(Indexer &indexer)
//    : indexer_(indexer) {
//}

//CommandType CommandHandler::determineCommandType(const std::string& command) {
//    static std::unordered_set<std::string> allowedCommands = {"SEARCH", "STATUS", "INDEXER", "GET", "ADD", "PUSH", "CLEAR"};

//    if (allowedCommands.count(command) > 0) {
//        return CommandType::COMMAND;
//    } else {
//        return CommandType::UNKNOWN;
//    }
//}

//void CommandHandler::processCommand(const std::string& command) {
//    CommandType type = determineCommandType(command);

//    switch (type) {
//    case CommandType::COMMAND:
//        if (command == "INDEXER") {
//            indexer_.processIndexingCommand();
//        } else if (command == "SEARCH") {
//            std::cout << "Processing SEARCH command." << std::endl;
//        } else if (command == "STATUS") {
//            std::cout << "Processing STATUS est une commande." << std::endl;
//        } else if (command == "GET") {
//            std::cout << "Processing GET est une commande." << std::endl;
//        } else if (command == "ADD") {
//            std::cout << "Processing ADD est une commande." << std::endl;
//        } else if (command == "PUSH") {
//            std::cout << "Processing PUSH est une commande." << std::endl;
//        } else if (command == "CLEAR") {
//            std::cout << "Processing CLEAR est une commande." << std::endl;
//        } else {
//            std::cout << "Unknown command: " << command << std::endl;
//        }
//        break;
//    case CommandType::UNKNOWN:
//        std::cout << "Unknown je ne connais pas la commande: " << command << std::endl;
//        break;
//    }
//}

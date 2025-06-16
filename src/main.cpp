#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  // std::cout << "$ ";

  std::vector<std::string> built_in_commands = {
    "type",
    "echo",
    "exit",
    "cd",
    "pwd",
    "ls",
    "cat",
    "clear",
    "help"
  };

  std::string input;
  // std::getline(std::cin, input);

  // std::cout << input << ": command not found " << std::endl;

  while(true){
    std::cout<<"$ ";
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<std::string> args;
    std::string word;
    while(ss >> word){
      args.push_back(word);
    }
    if(args.empty()){
      continue;
    }
    const std::string& command = args[0];
  
    // for(size_t i = 1; i < args.size(); ++i) {
    //   if (args[i].find(' ') != std::string::npos) {
    //     std::cerr << "Error: Arguments should not contain spaces." << std::endl;
    //     continue;
    //   }
    //   std::cout << "Argument " << i << ": " << args[i] << std::endl;
    // }


    // std::cout <<"INPUTE " <<input << std::endl;

    if (command == "exit" || command == "exit 0")
    {
      break;
    }

    const std::string str = "echo ";
    const int n = input.find("echo ");

    if (command == "echo")
    {
      std::cout << input.substr(n + str.length()) << std::endl;
      continue;
    }
    if (command == "type")
    {
      if (std::find(built_in_commands.begin(), built_in_commands.end(), args[1]) != built_in_commands.end()){
        const auto it = std::find(built_in_commands.begin(), built_in_commands.end(), args[1]);
        // std::cout << *it << std::endl;

        std::cout << args[1] << " is a shell builtin" << std::endl;
      } else {
        std::cout << args[1] << ": not found" << std::endl;
      }
      continue;
    }


    std::cout << input << ": command not found " << std::endl;
  }
}

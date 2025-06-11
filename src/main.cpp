#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  std::cout << "$ ";

  std::string input;
  // std::getline(std::cin, input);

  // std::cout << input << ": command not found " << std::endl;

  while(true){
    // std::cout<<"$ ";
    std::getline(std::cin, input);

    // std::cout <<"INPUTE " <<input << std::endl;

    if(input == "exit" || input == "exit 0"){
      break;
    }
    if(input.rfind("$ echo ",0) == 0){
      std::cout<< input << std::endl;
      std::cout<< input.substr(7) << std::endl;
    }


    std::cout << input << ": command not found " << std::endl;
  }
}

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
    const int n = input.find("echo ", 0);
    if(n == 0){
      std::cout<< input << " "<< n << std::endl;
      std::cout << input.substr(input.length() - 5) << std::endl;
      break;
    }


    std::cout << input << ": command not found " << std::endl;
  }
}

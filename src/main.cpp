#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<std::string> splitString(const std::string &str, char &separator)

{

  std::string token;
  std::vector<std::string> filepaths;
  std::stringstream pathstreams(str);

  while (std::getline(pathstreams, token, separator))
  {
    filepaths.push_back(token);
  }
  return filepaths;
}

fs::path findFileinpath(const std::string &fileName, const std::vector<std::string> &paths)
{

  for (const std::string &path : paths)
  {
    fs::path fullPath = fs::path(path) / fileName;
    if (fs::exists(fullPath) && fs::is_regular_file(fullPath))
    {
      return fullPath;
    }
  }

  return fs::path();
}

#include <iostream>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

// Function to split string by whitespace
std::vector<std::string> splitByWhitespace(const std::string &input)
{
  std::istringstream iss(input);
  std::vector<std::string> tokens;
  std::string word;
  while (iss >> word)
  {
    tokens.push_back(word);
  }
  return tokens;
}

std::vector<std::string> get_builtin_commands()
{
  std::string command = "zsh -c \"builtin\"";
  std::string result;
  std::vector<std::string> builtins = splitByWhitespace(result);
  char buffer[256];

  std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
  if (!pipe)
  {
    std::cerr << "Failed to run command." << std::endl;
    return std::vector<std::string>();
  }

  // Read the output from the zsh builtin command
  while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr)
  {
    result += buffer;
  }

  // Split output into a vector of strings

  // Output each built-in command
  // std::cout << "Zsh Built-in Commands (" << builtins.size() << " total):\n";
  // for (const auto &cmd : builtins)
  // {
  //   std::cout << "- " << cmd << "\n";
  // }

  return builtins;
}

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  // std::cout << "$ ";

  std::vector<std::string> built_in_commands = {
      "cp",
      "mv",
      "rm",
      "mkdir",
      "rmdir",
      "touch",
      "type",
      "echo",
      "exit",
      "cd", 
      "echo",
      "cat"
      "pwd",
      "clear",
      "help"};

  std::string input;
  // std::getline(std::cin, input);

  // std::cout << input << ": command not found " << std::endl;

  while (true)
  {
    std::cout << "$ ";
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<std::string> args;
    std::string word;
    while (ss >> word)
    {
      args.push_back(word);
    }
    if (args.empty())
    {
      continue;
    }
    const std::string &command = args[0];

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
      std::vector<std::string> builtins = get_builtin_commands();

      // if (std::find(built_in_commands.begin(), built_in_commands.end(), args[1]) != built_in_commands.end())
      if (std::find(builtins.begin(), builtins.end(), args[1]) != builtins.end())
      {
        std::cout << args[1] << " is a shell builtin" << std::endl;
        continue;
      }
      const char *path_env = std::getenv("PATH");
      if (!path_env)
      {
        std::cerr << "PATH environment variable not found." << std::endl;
        return 1;
      }

#ifdef _WIN32
      char pathDelimiter = ';';
#else
      char pathDelimiter = ':';
#endif

      std::string path_string(path_env);

      std::vector<std::string> paths = splitString(path_string, pathDelimiter);
      fs::path filePath = findFileinpath(args[1], paths);
      // std::cout << filePath<< std::endl;

      if (!filePath.empty())
      {
        std::cout << args[1] << " is " << filePath.string() << std::endl;
      }
      else
      {
        std::cout << args[1] << ": not found" << std::endl;
      }

      //   std::cout << args[1] << " is a shell builtin" << std::endl;
      // }
      // else
      // {
      //   std::cout << args[1] << ": not found" << std::endl;
      continue;
      // }
    }

    std::cout << input << ": command not found " << std::endl;
  }
}

std::vector<std::string> splitByWhitespace(const std::string &input)
{
  std::istringstream iss(input);
  std::vector<std::string> tokens;
  std::string word;
  while (iss >> word)
  {
    tokens.push_back(word);
  }
  return tokens;
}
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <experimental/filesystem>

namespace fs = std::filesystem;

std::string joinVector(const std::vector<std::string> &vec, char separator);
std::vector<std::string> splitString(const std::string &str, char &separator);
fs::path findFileinpath(const std::string &fileName, const std::vector<std::string> &paths);

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::vector<std::string> built_in_commands = {
      "type",
      "echo",
      "exit",
      "cd",
      "pwd"};
  std::string input;

#ifdef _WIN32
  char pathDelimiter = ';';
#else
  char pathDelimiter = ':';
#endif

  while (true)
  {
    std::cout << "$ ";
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<std::string> args;
    std::string word;

    const char *path_env = std::getenv("PATH");

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

    if (command == "pwd")
    {
      fs::path currentPath = fs::current_path();
      std::cout << currentPath.string() << std::endl;
      continue;
    }

    if (command == "cd")
    {

      if (args.size() < 2)
      {
        std::cerr << "cd: missing argument" << std::endl;
        continue;
      }

      const fs::path newPath = args[1];
      if (newPath.string() == "~")
      {

        const char *home_env = std::getenv("HOME");
        if (home_env)
        {
          fs::path homePath(home_env);
          if (fs::exists(homePath) && fs::is_directory(homePath))
          {
            fs::current_path(homePath);
            continue;
          }
          else
          {
            std::cerr << "cd: " << homePath.string() << ": No such file or directory" << std::endl;
            continue;
          }
        }
        else
        {
          std::cerr << "cd: HOME environment variable not set" << std::endl;
          continue;
        }
      }

      if (fs::exists(newPath) && fs::is_directory(newPath))
      {
        fs::current_path(newPath);
      }
      else
      {
        std::cerr << "cd: " << newPath.string() << ": No such file or directory" << std::endl;
        continue;
      }

      continue;
    }

    if (command == "echo")
    {
      // for (size_t i = 1; i < args.size(); ++i)
      // {
      //   std::cout << args[i];
      //   if (i < args.size() - 1)
      //   {
      //     std::cout << " ";
      //   }
      // }
      const std::string str = "echo ";
      const int n = input.find("echo ");
      std::string display = input.length() >= 2 
      && 
     ( input.front() == '"' 
      && 
      input.back() == '"' 
      || 
      input.front() == '\'' 
      && 
      input.back() == '\'' )
      ? 
      // input.substr(n + 1, input.length() - 3) 
      "CARAHAN"
      : 
      "LIYANA";
      // input.substr(n + str.length());

      // std::cout << args[1] <<std::endl;
      std::cout << display << std::endl;
      continue;
    }
    if (command == "type")
    {

      if (std::find(built_in_commands.begin(), built_in_commands.end(), args[1]) != built_in_commands.end())

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

      std::string path_string(path_env);

      std::vector<std::string> paths = splitString(path_string, pathDelimiter);
      fs::path filePath = findFileinpath(args[1], paths);

      if (!filePath.empty())
      {
        std::cout << args[1] << " is " << filePath.string() << std::endl;
      }
      else
      {
        std::cout << args[1] << ": not found" << std::endl;
      }

      continue;
      // }
    }

    if (path_env)
    {
      std::string path_string(path_env);

      std::vector<std::string> paths = splitString(path_string, pathDelimiter);
      fs::path filePath = findFileinpath(args[0], paths);

      if (!filePath.empty())
      {
        std::system(input.c_str());
      }
      else
      {
        std::cout << args[0] << ": command not found" << std::endl;
      }
      continue;
    }
    std::cout << input << ": command not found " << std::endl;
    continue;
  }
}

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

std::string joinVector(const std::vector<std::string> &vec, char separator)
{
  // std::string result;
  // for (const auto &str : vec)
  // {
  //   if (!result.empty())
  //   {
  //     result += separator; // here there are more memory allocations than necessary
  //   }
  //   result += str;
  // }
  // return result;

  std::ostringstream result;
  for (const auto &str : vec) // use auto to loop over elements of the vector and avoid type issues
  // use size_t(unsigned integer type) for indexing
  {
    if (!result.str().empty())
    {
      result << separator;
    }
    result << str;
  }
  return result.str();
}
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <sstream> // Include this to use std::istringstream
#include <string>
#include <vector>

int main()
{
  std::ifstream infile("input.txt");
  std::string line;
  int fileIndex = 1;

  while (getline(infile, line))
  {
    std::string latitude, longitude;
    std::istringstream iss(line); // This will work after including <sstream>
    if (!(iss >> latitude >> longitude))
    {
      std::cerr << "Error parsing line: " << line << std::endl;
      continue; // Skip to the next line if parsing fails
    }

    pid_t pid = fork();

    if (pid == 0)
    { // This is the child process
      std::string filename = "file" + std::to_string(fileIndex++) + ".json";
      std::string command = "curl -o " + filename + " 'https://api.open-meteo.com/v1/forecast?latitude=" + latitude + "&longitude=" + longitude + "&current_weather=True'";
      execlp("/bin/sh", "sh", "-c", command.c_str(), nullptr);
      exit(1); // Exit child if execlp fails
    }
    else if (pid > 0)
    { // This is the parent process
      int status;
      wait(&status); // Wait for child to finish
      if (status != 0)
      {
        std::cerr << "Error executing curl command\n";
      }
    }
    else
    {
      std::cerr << "Failed to fork\n";
      return 1;
    }
  }

  return 0;
}

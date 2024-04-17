#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void fetchWeatherDataInParallel(const char *inputFile)
{
  std::ifstream infile(inputFile);
  std::string line;
  std::vector<pid_t> children;
  int fileIndex = 1;

  while (getline(infile, line))
  {
    std::istringstream iss(line);
    std::string latitude, longitude;
    if (!(iss >> latitude >> longitude))
    {
      std::cerr << "Error parsing line: " << line << std::endl;
      continue;
    }

    pid_t pid = fork();
    if (pid == 0)
    { // Child process
      std::string filename = "parallelfile" + std::to_string(fileIndex) + ".json";
      std::string command = "curl -o " + filename + " 'https://api.open-meteo.com/v1/forecast?latitude=" + latitude + "&longitude=" + longitude + "&current_weather=True'";
      std::cerr << "Child process (" << getpid() << ") saving to: " << filename << std::endl;
      execlp("/bin/sh", "sh", "-c", command.c_str(), nullptr);
      std::cerr << "Failed to execute command: " << command << std::endl;
      exit(1); // Exit if execlp fails
    }
    else if (pid > 0)
    { // Parent process
      children.push_back(pid);
      fileIndex++; // Increment in the parent process to ensure uniqueness
    }
    else
    {
      std::cerr << "Failed to fork\n";
      exit(1);
    }
  }

  // Wait for all children to finish
  for (pid_t pid : children)
  {
    int status;
    waitpid(pid, &status, 0);
  }
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <input_file>\n";
    return 1;
  }
  fetchWeatherDataInParallel(argv[1]);
  return 0;
}

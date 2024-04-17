#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void fetchWeatherDataSerially(const char *inputFile)
{
  std::ifstream infile(inputFile);
  std::string line;
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
      std::string filename = "serialfile" + std::to_string(fileIndex) + ".json";
      std::string command = "curl -o " + filename + " 'https://api.open-meteo.com/v1/forecast?latitude=" + latitude + "&longitude=" + longitude + "&current_weather=True'";
      execlp("/bin/sh", "sh", "-c", command.c_str(), nullptr);
      exit(1); // Should only reach here if execlp fails
    }
    else if (pid > 0)
    { // Parent process
      int status;
      wait(&status); // Wait for child to finish
      fileIndex++;   // Increment fileIndex after child process completes
    }
    else
    {
      std::cerr << "Failed to fork\n";
      exit(1);
    }
  }
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <input_file>\n";
    return 1;
  }
  fetchWeatherDataSerially(argv[1]);
  return 0;
}

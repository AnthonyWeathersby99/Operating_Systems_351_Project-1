#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " <number of files>\n";
    return 1;
  }

  int numberOfFiles = atoi(argv[1]);
  for (int fileNum = 1; fileNum <= numberOfFiles; ++fileNum)
  {
    string fileName = "file" + to_string(fileNum) + ".json";
    cout << "Generated file name: " << fileName << endl;
  }

  return 0;
}

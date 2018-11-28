#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

// Joeseph Fritz, Mason Protsman, Andrew Phipps
// 1730 - newer.cpp

int main(int argc, char* argv[]){
  // Ensure the correct number of arguments were provided.
  if(argc != 4){
    cout << "Input error! Not enough arguments provided!" << endl;
    cout << "Input should look like: ./newer (-a | -m | -c) FILE_1 FILE_2" << endl;
    return -1;
  }

  // Open File1 and File2
  int fd1 = open(argv[2], O_RDONLY);
  int fd2 = open(argv[3], O_RDONLY);

  // Print and error if an open error occured
  if(fd1 < 0 || fd2 < 0){
    perror("open error");
    return -1;
  }

  struct stat file1;
  struct stat file2;

  // Print an error if something when wrong when getting the stats for file1 or file2
  if((fstat(fd1, &file1) == -1) || (fstat(fd2, &file2) == -1)){
    perror("stat error");
    return -1;
  }

  int f1Age = 0;
  int f2Age = 0;
  char option = (argv[1])[1];
  // Determine the age of each file based on the provided arguement.
  switch(option){
    // Access time
    case 'a':
      f1Age = file1.st_atime;
      f2Age = file2.st_atime;
      break;
    // Modification time
    case 'm':
      f1Age = file1.st_mtime;
      f2Age = file2.st_mtime;
      break;
    // Change time
    case 'c':
      f1Age = file1.st_ctime;
      f2Age = file2.st_ctime;
      break;
    // Error/Wrong arg
    default:
      cout << "Invalid argument provided! Choose between (-a | -m | -c)." << endl;
      return -1;
  }

  // If file1's age is greater it is newer
  if(f1Age > f2Age)
    cout << "File: " << argv[2] << " is newer then File: " << argv[3] << endl;
  // Otherwise (file2's age is greater), it is newer
  else
    cout << "File: " << argv[3] << " is newer then File: " << argv[2] << endl;

  return 0;
}

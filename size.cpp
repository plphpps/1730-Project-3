#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

#define BUFFSIZE 5

// Joeseph Fritz, Mason Protsman, Andrew Phipps
// 1730 - size.cpp

int main(int argc, char* argv[]){
  int totalSize = 0;
  
  // Determine the number of files. If the number of args is greater than 1 (meaning there's more than just ./size), then set the file count to argc - 1. Otherwise (there isn't anything but ./size), set the file count to one.
  int fileCount = (argc > 1) ? argc - 1 : 1;

  // Sort through every file provided by the user.
  for(int i = 0; i < fileCount; i++){
    // Get the file descriptor. If there is more than one argc then open the file at argv[index + 1] (add one to account for ./size). Otherwise, set it to standard input.
    int fd = (argc != 1) ? open(argv[i + 1], O_RDONLY) : STDIN_FILENO;

    // Check for errors opening the file.
    if(fd < 0){
      perror("error opening file");
      return fd;
    }

    int size = 0;
    // If the file desriptor is standard in read and count the number of bytes from input.
    if(fd == STDIN_FILENO){
      int r = 0;
      char buf[BUFFSIZE];
      while((r = read(fd, buf, BUFFSIZE)) > 0){
	size += r;

	// If the input didn't end in a new line add a new line so that when the size is printed on another line.
	if(r < BUFFSIZE && buf[r - 1] != '\n') cout << endl;
      }
    }
    // The file descriptor is not standard in, meaning a file was opened. Use fstat to find the size of the file.
    else{
      struct stat st;
      if(fstat(fd, &st) == -1){
	perror("stat");
	return -1;
      }

      size = st.st_size;
    }

    // Print the size.
    cout << size << endl;

    totalSize += size;
  }

  // If there was more then one file print the total at the end.
  if(argc != 1)
    cout << "total: " << totalSize << endl;

  return 0;
}

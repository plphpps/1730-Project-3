#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

// Joeseph Fritz, Mason Protsman, Andrew Phipps
// 1730 - dirlist.cpp

int main(void){
  DIR* dirp;
  // Try and open the present working directory. If something goes wrong (opendir returns null), then print an error.
  if((dirp = opendir(".")) == 0){
    perror("open error");
    return -1;
  }

  struct dirent* dp;
  // While the next directory entry is not null, print out the file name.
  while((dp = readdir(dirp)) != 0)
    cout << dp->d_name << endl;

  return 0;
}

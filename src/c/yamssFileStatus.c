#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <gpfs.h>

int main(int argc, char **argv) {
  
  gpfs_winattr_t wt;

  if(argc!=2) {
    fprintf(stderr,"Usage: yamssFileStatus FILE\n");
    exit(1);
  }

  if(gpfs_get_winattrs_path(argv[1],&wt)) {
    fprintf(stderr, "gpfs_get_winattrs_path failed, %s\n", strerror(errno));
    exit(1);
  }

  if(wt.winAttrs&GPFS_WINATTR_OFFLINE) printf("offline\n");
  else printf("online\n");

  return 0;
}


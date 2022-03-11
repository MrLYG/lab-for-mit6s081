#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc != 2) 
  {
      fprintf(2,"usage:sleep <tiem>\n");
      exit(1);
  }
  fprintf(1,"sleep start");
  sleep(atoi(argv[1]));
  fprintf(1,"sleep end");
  exit(0);
}

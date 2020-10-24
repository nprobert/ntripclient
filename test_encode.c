//
// UDP Client Socket
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern int rsu_send(int sock, const char *buf, int num);

int main(int argc, char **argv)
{
  char buf[2000];
  memset(buf, 0x5a, sizeof(buf));
  int i;
  
  for(i=0; i<1100; i+=256) {
    printf("TESTING %d\n", i);
    int n = rsu_send(-1, buf, i);    
    printf("TESTED %d = %d\n", i, n);
    
    if (n<0)
      break;
  }
}

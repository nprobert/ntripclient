//
// UDP Client Socket
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern int j2735_encode(const char *raw, int size, char *buf, int max);
extern int udp_send(int sock, const void *buf, size_t n);

int rsu_send(int sock, const char *buf, int num)
{
  char dat[1400];
  memset(dat, 0, sizeof(dat));

  if (num <= 0)
    return num;

  // clip
  if (num  > 1023)
    num = 1023;

  // encoded size
  int n = j2735_encode(buf, num, dat, sizeof(dat));

  // test only
  if (sock <0)
    return n;
  
  if (n > 0)
  {
    // connected udp socket
    if (udp_send(sock, dat, n) > 0)
      return num;           // return #rtcm send
  }
  else {
    fprintf(stderr, "J2735 RTCM encoding failed\n");
  }
  return -1;
}

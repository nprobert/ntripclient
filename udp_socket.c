//
// UDP Client Socket
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#include <netdb.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <string.h>

int udp_client( const char *host, const char *service )
{
  int     sock;       /* tcp socket */
  struct addrinfo     hints, *res, *ressave;
  
  /* default IPv6 localhost */
  if ( !host || !strlen(host) )
    host = "ip6-localhost";
  
    /* get address information */   
  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  if ( getaddrinfo(host, service, &hints, &res) )
  {
    return -1;
  }
  ressave = res;
  
  while (res)
  {
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
      continue;   // ignore
    }

    // connected (allows send()/write() to be used)
    if ( connect(sock, res->ai_addr, res->ai_addrlen) == 0 ) {
      break;      // success
    }

    // next    
    close(sock);
    res = res->ai_next;
  }
  
  if ( !res )
  {
    return -1;
  }
  
  freeaddrinfo(ressave);
  
  return sock;
}

int udp_send(int sock, const void *buf, size_t num)
{
  int n = send(sock, buf, num, 0);
  if(n <= 0)
  {
    perror("Could not write UDP socket");
  }
  return n;
}

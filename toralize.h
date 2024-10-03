/* toralize.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

socket()
connect()
close()
htons() // from port number - cn
inet_adder()
/*
9050

10101100 10101100 - port number in binary
*/

#define PROXY  "127.0.0.1"
#define PROXYPORT 9050

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

/*
            +----+----+----+----+----+----+----+----+----+----+....+----+
            		| VN | CD | DSTPORT |      DSTIP        | USERID   |NULL|
            +----+----+----+----+----+----+----+----+----+----+....+----+
# of bytes:	       1    1      2             4           variable     1
*/

struct proxy_request {
  int8 vn;
  int32 cd;
  int16 dstport;
  int32 dstip;
  unsigned char userid[8];
};
typedef struct proxy_request Req;

/*
          +----+----+----+----+----+----+----+----+
          		| VN | CD | DSTPORT  |     DSTIP    |
          +----+----+----+----+----+----+----+----+
# of bytes: 	   1    1      2              4
*/

struct proxy_response {
  int8 vn;
  int8 cd;
  int16 _;
  int32 __;
};
typedef struct proxy_response Res;

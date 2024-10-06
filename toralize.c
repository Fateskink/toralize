/* toralizer.c */
#include "toralize.h"

int main(int argc, char *argv[])
{
  char *host;
  int port, s;

  struct sockaddr_in sock;

  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s <host> <port>\n",
            argv[0]);

    return -1;
  }

  host = argv[1];
  port = atoi(argv[2]);

  /*
  AF_INET là một hằng số được sử dụng trong lập trình mạng
  để chỉ định giao thức địa chỉ IPv4
  (Internet Protocol Version 4 | 32-bit).
  Khi tạo một socket trong ngôn ngữ lập trình (như C, C++, hoặc Python),
  bạn phải cung cấp một "address family" (họ địa chỉ),
  và AF_INET đại diện cho các địa chỉ IPv4.

  SOCK_STREAM: Xác định rằng socket này sẽ sử dụng giao thức TCP
  (giao thức truyền dữ liệu tin cậy, có kết nối).
  */
  s = socket(AF_INET, SOCK_STREAM, 0);

  if (s < 0)
  {
    perror("Invalid socket"); // system error messages

    return -1;
  }

  // Chỉ định "family" (họ) của địa chỉ được sử dụng trong giao tiếp mạng
  sock.sin_family = AF_INET;

  // Số cổng (port) được sử dụng để giao tiếp trên mạng.
  // htons() để đảm bảo thứ tự byte đúng khi truyền dữ liệu qua mạng
  sock.sin_port = htons(PROXYPORT);

  // Địa chỉ IP
  sock.sin_addr.s_addr = inet_addr(PROXY);

  /*
  (struct sockaddr *)&sock:
  sock là một cấu trúc kiểu sockaddr_in,
  chứa thông tin về địa chỉ IP và số cổng mà bạn muốn kết nối.
  sockaddr_in là cấu trúc chứa thông tin chi tiết cho giao thức IPv4.
  Tuy nhiên, hàm connect yêu cầu địa chỉ
  phải được truyền vào dưới dạng sockaddr (kiểu chung),
  vì vậy ta cần ép kiểu (struct sockaddr *) để đảm bảo đúng định dạng.

  sizeof(sock)
  Hàm connect cần biết độ dài của địa chỉ bạn đang truyền
  để đảm bảo kết nối được thiết lập đúng.

  # Terminal command (tm) : man 2 connect
    Upon successful completion, a value of 0 is returned.
    Otherwise, a value of -1 is returned and
    the global integer variable errno is set to indicate the error.

  # Prerequisite: Your device must be installed tor
    127.0.0.1 9050 is the default port value of tor
    to run toralize
  */
  if (connect(s, (struct sockaddr *)&sock, sizeof(sock)))
  {
    perror("Connect failed");

    return -1;
  }

  printf("Connect to proxy\n");
  close(s);

  return 0;
}

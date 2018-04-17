#include <iostream>
#include <functional>
#include <fstream>
#include <thread>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cctype>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <cstdlib>
#include <cstdint>
#include <memory>

using namespace std;

const string SERVER_STRING = "Server: myhttpd/1.0.0\r\n";
static const int num_threads = 20;

class Server
{
public:
    Server(unsigned short port);
    ~Server();
private:
  int thread_counter = 0;
  thread thread_pool[num_threads];
  void send_headers(int client, string status, string type);
  int startup(unsigned short port);
  void accept_request(int client_socket);
  void bad_request(int client_socket);
  int get_line(int client_socket, string &line, int count);
  void headers(int client_socket, string header);
  void not_found(int client_socket);
  void serve_file(int client_socket, string filename);
  void unimplemented(int client_socket);
};
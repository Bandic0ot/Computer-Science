#ifndef tcp
#define tcp

void create_connection(char *address, char *port, int *sock);

void start_listen(int *listen_sock, char *port);

void handle_connection(int listen_sock);

char *create_packet(char *data, uint32_t size);

uint32_t parse_packet(char *packet, char *buffer);

#endif //tcp

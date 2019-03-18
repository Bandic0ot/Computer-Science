#ifndef tcp
#define tcp

void create_connection(char *address, char *port, int *sock);

void start_listen(int *listen_sock, char *port);

void handle_connection(int listen_sock);

char *create_packet(char *data, uint32_t size);

uint32_t parse_packet(char *packet, char *buffer);

void send_all(int sock, char *data, uint32_t size);
int recv_all(int sock, char *data, uint32_t size);

// Appends the second byte array to the first.
char *append_byte_array(char *byte1, char *byte2, uint32_t size1, uint32_t size2);

#endif //tcp

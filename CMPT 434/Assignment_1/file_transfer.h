#ifndef file_transfer
#define file_transfer

int file_exists(char *file);

int file_to_buffer(char *file, char *buffer);
void buffer_to_file(char *file, char *buffer, int bytes_recv);

void send_all(int sock, char *msg, int msg_length);
int recv_all(int sock, char *buffer, int buffer_length);

#endif
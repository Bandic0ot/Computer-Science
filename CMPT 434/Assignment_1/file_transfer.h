/* Matthew Mulenga
 * mam558
 * 11144528
 */

#ifndef file_transfer
#define file_transfer

int file_exists(char *file);

int file_to_buffer(char *file, char *buffer);
void buffer_to_file(char *file, char *buffer, int bytes_recv);

void pack_length(char *msg, int msg_length, char *buffer);
int unpack_length(char *msg);

void send_all(int sock, char *msg, int msg_length);
int recv_all(int sock, char *buffer, int buffer_length);
void send_status(int sock, char *msg);
int recv_status(int sock);

void *get_in_addr(struct sockaddr *sa);

#endif
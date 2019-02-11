/* Matthew Mulenga
 * mam558
 * 11144528
 */

#ifndef udp
#define udp

void serialize_frame(int *s, int *a, char *data, int *data_len, char *buffer);
void unserialize_frame(int *s, int *a, int *data_len, char *buffer);

void send_frame(int sock, char *frame);
int recv_frame(int sock, int *s, int *a, char *data, int *length);

#endif
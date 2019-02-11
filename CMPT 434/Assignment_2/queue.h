/* Matthew Mulenga
 * mam558
 * 11144528
 */

#ifndef queue
#define queue

#define MAX_DATA_SIZE 100

void initialize(int size);

int size();
int empty();
int full();
void enqueue(char **queue, char *item);
char *dequeue(char **queue);

#endif
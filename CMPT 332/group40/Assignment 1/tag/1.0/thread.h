// Structure and typedef from week1-threads tutorial material.
typedef int(*thread_entry)(int);

/* Store information for thread */
struct thread_info {
    int id;
    thread_entry entry;
    void *thread; /* point to arch specific thread info */
};


// Create a new thread.
int thread_create(struct thread_info *);

// Tell a thread to sleep.
void thread_sleep(int deadline);

// Exit from a thread.
void thread_exit();

// Kill another thread.
int thread_kill(int pid);

// Parse the given arguments - from week1-threads tutorial material.
int parse_args(int argc, char *argv[]);

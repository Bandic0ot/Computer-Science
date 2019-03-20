Commands to run the program.

1) `make`
2) ./logger [PORT] [TRANSMISSION RANGE] [NUMBER OF NODES]
3) ./node [ID] [DATA] [PORT] [LOGGER HOSTNAME] [LOGGER PORT]

(Each node must be run separately.)
NOTE: Node IDs must be in sequential order starting from 0.
eg) ./logger 30080 250 3
    ./node 0 hello 30081 0.0.0.0 30080
    ./node 1 hello 30082 0.0.0.0 30080
    ./node 2 hello 30083 0.0.0.0 30080
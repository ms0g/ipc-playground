CC = gcc
MODE = -std=c99
DEBUG = -g
CFLAGS =  -Wall -c $(DEBUG)
LFLAGS =  -Wall $(DEBUG)

all:
	$(CC) pipe.c  $(LFLAGS) -o pipe
	$(CC) fifo_producer.c  $(LFLAGS) -o fifo_producer
	$(CC) fifo_consumer.c $^ $(LFLAGS) -o fifo_consumer
	$(CC) signal_sender.c $^ $(LFLAGS) -o signal_sender
	$(CC) signal_receiver.c $^ $(LFLAGS) -o signal_receiver
	$(CC) mq_producer.c $^ $(LFLAGS) -o mq_producer
	$(CC) mq_consumer.c $^ $(LFLAGS) -o mq_consumer
	$(CC) flocking.c $^ $(LFLAGS) -o flocking
	$(CC) shm_producer.c $^ $(LFLAGS) -o shm_producer
	$(CC) shm_consumer.c $^ $(LFLAGS) -o shm_consumer
	$(CC) uds_server.c $^ $(LFLAGS) -o uds_server
	$(CC) uds_client.c $^ $(LFLAGS) -o uds_client
	$(CC) xsi_sem.c $^ $(LFLAGS) -o xsi_sem
	$(CC) posix_sem.c $^ $(LFLAGS) -lpthread  -o posix_sem

test:
	sh runtest.sh
clean:
	rm -f fifo_consumer fifo_producer pipe  signal_sender signal_receiver \
	mq_consumer mq_producer flocking shm_consumer shm_producer uds_server \
	uds_client xsi_sem posix_sem


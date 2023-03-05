#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

/* Do not touch these two */
#define HOST "127.0.0.1"
#define PORT 10001

#include "common.h"

/* Our unqiue layer 2 ID */
static int ID = 123131;
static struct timeval sendtime;
static struct timeval endtime;

/* Function which our protocol implementation will provide to the upper layer. */
int recv_frame(char *buf, int size)
{
	/* TODO 1.1: Call recv_byte() until we receive the frame start
	 * delimitator. This operation makes this function blocking until it
	 * receives a frame. */
	char byte1 = recv_byte(), byte2 = recv_byte();
	while (byte1 != DLE || byte2 != STX) {
		byte1 = byte2;
		byte2 = recv_byte();
	}


	/* TODO 2.1: The first two 2 * sizeof(int) bytes represent sender and receiver ID */
	char srcdest[8];
	// for some reason sizeof(struct Frame)=44 instead of 42,
	// sender sends 2 extra bytes of data that I skip below
	recv_byte();
	recv_byte();
	for (int i = 0; i < 2 * sizeof(int); i++) {
		srcdest[i] = recv_byte();
	}
	int src = *((int *)srcdest);
	int dest = *((int *)(srcdest + 4));
	/* TODO 2.2: Check that the frame was sent to me */
	// printf("src = %d\n", src);
	// printf("dest = %d\n", dest);
	if (dest != ID) {
		return 0;
	}
	// get timevalue from struct Frame (size is 16 bytes)
	// sender sends 4 extra bytes of data that I skip below
	recv_byte();
	recv_byte();
	recv_byte();
	recv_byte();
	char sendtime_char[16];
	for (int i = 0; i < sizeof(struct timeval); i++) {
		sendtime_char[i] = recv_byte();
	}
	sendtime = *((struct timeval *)sendtime_char);
	/* TODO 1.2: Read bytes and copy them to buff until we receive the end of the frame */
	char new_byte;
	size = 0;
	for (int i = 0; i < MAX_SIZE + 2; i++)
	{
		new_byte = recv_byte();
		if (new_byte == DLE) {
			new_byte = recv_byte();
			/* Am primit DLE ETX */
			if (new_byte == ETX) {
				// end of transmission
				break;
			}
			/* Dupa DLE, trebuie sa primim alt DLE,
				altfel frame-ul nu este bine structurat */ 
			// if (new_byte != DLE) {
			// 	return -1;
			// }
		}
		buf[size++] = new_byte;
	}
	
	// set endtime struct at the end to increase accuracy
	gettimeofday(&endtime, 0);

	/* If everything went well return the number of bytes received */
	return size;
}

int main(int argc,char** argv){
	/* Do not touch this */
	init(HOST,PORT);


	// char c;

	// /* Wait for the start of a frame */
	// char c1,c2;
	// c1 = recv_byte();
	// c2 = recv_byte();

	// /* Cat timp nu am primit DLE STX citim bytes */
	// while((c1 != DLE) && (c2 != STX)) {
	// 	c1 = c2;
	// 	c2 = recv_byte();
	// }


	// printf("%d ## %d\n",c1, c2);
	// c = recv_byte();
	// printf("%c\n", c);

	// c = recv_byte();
	// printf("%c\n", c);

	// c = recv_byte();
	// printf("%c\n", c);

	// c = recv_byte();
	// printf("%c\n", c);

	// c = recv_byte();
	// printf("%c\n", c);

	// c = recv_byte();
	// printf("%c\n", c);

	/* TODO 1.0: Allocate a buffer and call recv_frame */
	char buffer[MAX_SIZE];
	int size = recv_frame(buffer, MAX_SIZE);
	if (size < 0) {
		fprintf(stderr, "Corrupted frame!");
		goto end;
	}
	if (size == 0) {
		printf("Intercepted message meant for another computer\n");
		goto end;
	}
	printf("%s\n", buffer);

	/* TODO 3: Measure latency in a while loop for any frame that contains
	 * a timestamp we receive, print frame_size and latency */
	long seconds = endtime.tv_sec - sendtime.tv_sec;
    long microseconds = endtime.tv_usec - sendtime.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
	printf("Latency = %lf\n", elapsed);

end:
	printf("[RECEIVER] Finished transmission\n");
	return 0;
}

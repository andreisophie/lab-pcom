#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#include "link_emulator/lib.h"

#define TEXT100 "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean m"
#define TEXT300 "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec."

/* We don't touch this */
#define HOST "127.0.0.1"
#define PORT 10000

/* Here we have the Frame structure */
#include "common.h"

/* Our unqiue layer 2 ID */
static int ID = 123131;

/* Function which our protocol implementation will provide to the upper layer. */
int send_frame(char *buf, int size, int destID)
{

	/* TODO 1.1: Create a new frame. */
	struct Frame new_frame;

	/* TODO 1.2: Copy the data from buffer to our frame structure */
	// add header
	new_frame.frame_delim_start[0] = DLE;
	new_frame.frame_delim_start[1] = STX;
	// add data itself
	// strncpy(new_frame.payload, buf, MAX_SIZE);
	int frame_index = 0;
	for (int i = 0; i < size; i++) {
		if (buf[i] == DLE) {
			new_frame.payload[frame_index++] = DLE;
		}
		new_frame.payload[frame_index++] = buf[i];
	}
	new_frame.payload[frame_index++] = '\0';
	// add end of transmission
	new_frame.frame_delim_end[0] = DLE;
	new_frame.frame_delim_end[1] = ETX;

	/* TODO 2.1: Set the destination and source */
	new_frame.source = ID;
	new_frame.dest = destID;
	
	/* TODO 1.3: We can cast the frame to a char *, and iterate through sizeof(struct Frame) bytes
	 calling send_bytes. */
	char *package = (char *)&new_frame;
	for (int i = 0; i < sizeof(struct Frame); i++) {
		send_byte(package[i]);
	}
	// printf("sizeof(struct Frame)=%d\n", sizeof(struct Frame));

	// set time of send at the end, to minimize delay
	gettimeofday(&new_frame.sendtime, 0);
	// printf("sizeof(struct timeval)=%d\n", sizeof(struct timeval));

	/* if all went all right, return 0 */
	return 0;
}

int main(int argc,char** argv){
	// Don't touch this
	init(HOST,PORT);

	/* Send Hello */
	// send_byte(DLE);
	// send_byte(STX);
	// send_byte('H');
	// send_byte('e');
	// send_byte('l');
	// send_byte('l');
	// send_byte('o');
	// send_byte('!');
	// send_byte(DLE);
	// send_byte(ETX);

	/* TODO 1.0: Get some input in a buffer and call send_frame with it */
	// char buffer[MAX_SIZE] = "Mama ta!";
	// send_frame(buffer, strlen(buffer), 123131);

	/* TODO 3.1: Get a timestamp of the current time copy it in the the payload */

	/* TODO 3.0: Upload the maximum size of the payload in Frame to 100, send the frame */
	char buffer2[MAX_SIZE] = TEXT100;
	send_frame(buffer2, strlen(buffer2), 123131);
	/* TODO 3.0: Upload the maximum size of the payload in Frame to 300, send the frame */
	// char buffer3[MAX_SIZE] = TEXT300;
	// send_frame(buffer3, strlen(buffer3), 123131);

	return 0;
}

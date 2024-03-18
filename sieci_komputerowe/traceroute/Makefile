CC=gcc
CFLAGS=-std=gnu99
LDFLAGS=-lm
TARGET=traceroute
SRC=main.c traceroute.c icmp_send.c icmp_receive.c icmp_checksum.c utilities.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

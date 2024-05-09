# Ping Function

The `ping` function is a network diagnostic tool used to test the reachability of a host on an IP network. It sends ICMP (Internet Control Message Protocol) packets to the target host and waits for a response. If the host is reachable and functioning correctly, it will respond to the ICMP packets with its own ICMP packets.

## ICMP Structure

The `ICMP` structure is used to store the information contained in an ICMP packet. In C, it is defined as follows:

```c
typedef struct s_icmp {
	uint8_t		type;
	uint8_t		code;
	uint16_t	checksum;
	uint16_t	id;
	uint16_t	seq;
}	t_icmp;
```

Each field in the structure represents a part of the ICMP packet:

- `type`: The type of the ICMP message. For example, an echo (ping) request is type 8, and an echo (ping) reply is type 0.
- `code`: The subtype of the message. For echo (ping) messages, this field is usually 0.
- `checksum`: A checksum to verify that the packet has not been corrupted during transport.
- `id`: A unique identifier for the message. When a reply is received, the ID of the request is compared to the ID of the reply to ensure they match.
- `seq`: A sequence number for the message. This allows different messages sent from the same host to be distinguished from each other.
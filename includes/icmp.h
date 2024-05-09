#ifndef FT_PING_H
#define FT_PING_H

#include <stdint.h>

enum e_type {
	ICMP_ECHO_REPLY = 0,
	ICMP_ECHO = 8,
	ICMP_TIME_EXCEEDED = 11,
	ICMP_DEST_UNRECHEBLE = 3,
	SIZE_TYPE_ICMP // need to always at last
};

enum e_code {
	SIZE_CODE_ICMP // need to always at last
};

typedef struct s_icmp {
	uint8_t		type;
	uint8_t		code;
	uint16_t	checksum;
	uint16_t	id;
	uint16_t	seq;
}	t_icmp;

#endif
/*
 * network.h
 *
 *  Created on: Feb 22, 2016
 *      Author: root
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <stdint.h>
#include <stdlib.h>
#include "nbt.h"
#include <pthread.h>
#include "inventory.h"
#ifdef __MINGW32__
# include <winsock2.h>
#endif
#include "accept.h"
#include <unistd.h>
#include "globals.h"

typedef uint8_t mcbool;

struct __attribute__((__packed__)) encpos {
		int32_t z :26;
		int32_t y :12;
		int32_t x :26;
};

struct __attribute__((__packed__)) uuid {
		uint64_t uuid1;
		uint64_t uuid2;
};

#ifdef MC_VERSION_1_8_9
#include "packet1.8.h"
#elif MV_VERSION_1_9_4
#include "packet1.9.h"
#elif MV_VERSION_1_10
#include "packet1.10.h"
#endif

#define STATE_HANDSHAKE 0
#define STATE_STATUS 1
#define STATE_LOGIN 2
#define STATE_PLAY 3

void swapEndian(void* dou, size_t ss);

int getVarIntSize(int32_t input);

int getVarLongSize(int64_t input);

int writeVarInt(int32_t input, unsigned char* buffer);

int writeVarLong(int64_t input, unsigned char* buffer);

int readVarInt(int32_t* output, unsigned char* buffer, size_t buflen);

int readVarLong(int64_t* output, unsigned char* buffer, size_t buflen);

int writeString(char* input, unsigned char* buffer, size_t buflen);

int readString(char** output, unsigned char* buffer, size_t buflen);

ssize_t readPacket(struct conn* conn, unsigned char* buf, size_t buflen, struct packet* packet);

ssize_t writePacket(struct conn* conn, struct packet* packet);

int writeVarInt_stream(int32_t input,
#ifdef __MINGW32__
		SOCKET
#else
		int
#endif
		fd);

int readVarInt_stream(int32_t* output,
#ifdef __MINGW32__
		SOCKET
#else
		int
#endif
		fd);
#endif /* NETWORK_H_ */
/*
 * game.h
 *
 *  Created on: Dec 23, 2016
 *      Author: root
 */

#ifndef GAME_H_
#define GAME_H_

#include "world.h"
#include "entity.h"
#include "hashmap.h"
#include <pthread.h>

void player_openInventory(struct player* player, struct inventory* inv);

void flush_outgoing(struct player* player);

float randFloat();

void playSound(struct world* world, int32_t soundID, int32_t soundCategory, float x, float y, float z, float volume, float pitch);

void dropPlayerItem(struct player* player, struct slot* drop);

void dropEntityItem_explode(struct entity* entity, struct slot* drop);

void dropBlockDrop(struct world* world, struct slot* slot, int32_t x, int32_t y, int32_t z);

void dropBlockDrops(struct world* world, block blk, struct player* breaker, int32_t x, int32_t y, int32_t z);

void loadPlayer(struct player* to, struct player* from);

void loadEntity(struct player* to, struct entity* from);

void onInventoryUpdate(struct player* player, struct inventory* inv, int slot);

void tick_world(struct world* world);

void sendMessageToPlayer(struct player* player, char* text, char* color);

void sendMsgToPlayerf(struct player* player, char* color, char* fmt, ...);

void broadcast(char* text, char* color);

void broadcastf(char* color, char* fmt, ...);

#define BEGIN_BROADCAST(players) BEGIN_HASHMAP_ITERATION(players) struct player* bc_player = (struct player*)value; {
#define BEGIN_BROADCAST_DIST(distfrom, dist) BEGIN_HASHMAP_ITERATION(distfrom->world->players) struct player* bc_player = (struct player*)value; if(entity_distsq(bc_player->entity, distfrom) < dist * dist) {
#define BEGIN_BROADCAST_DISTXYZ(x, y, z, players, dist) BEGIN_HASHMAP_ITERATION(players) struct player* bc_player = (struct player*)value; if (entity_distsq_block(bc_player->entity, x, y, z) < dist * dist) {
#define BEGIN_BROADCAST_EXCEPT(players, except) BEGIN_HASHMAP_ITERATION(players) struct player* bc_player = (struct player*)value; if (bc_player != except) {
#define BEGIN_BROADCAST_EXCEPT_DIST(except, distfrom, dist) BEGIN_HASHMAP_ITERATION(distfrom->world->players) struct player* bc_player = (struct player*)value; if (bc_player != except && entity_distsq(bc_player->entity, distfrom) < dist * dist) {
#define END_BROADCAST(players) } END_HASHMAP_ITERATION(players)

/*
 #define BEGIN_BROADCAST_DIST(distfrom, dist) for (size_t i = 0; i < distfrom->world->players->size; i++) {struct player* bc_player = (struct player*) distfrom->world->players->data[i];if (bc_player != NULL && entity_distsq(bc_player->entity, distfrom) < dist * dist) {
 #define BEGIN_BROADCAST_DISTXYZ(x, y, z, players, dist) for (size_t i = 0; i < players->size; i++) {struct player* bc_player = (struct player*) players->data[i];if (bc_player != NULL && entity_distsq_block(bc_player->entity, x, y, z) < dist * dist) {
 #define BEGIN_BROADCAST_EXCEPT_DIST(except, distfrom, dist) for (size_t i = 0; i < distfrom->world->players->size; i++) {struct player* bc_player = (struct player*) distfrom->world->players->data[i];if (bc_player != NULL && bc_player != except && entity_distsq(bc_player->entity, distfrom) < dist * dist) {
 #define BEGIN_BROADCAST(players) if(players->mc) pthread_rwlock_rdlock(&players->data_mutex); for (size_t i = 0; i < players->size; i++) {struct player* bc_player = (struct player*) players->data[i];if (bc_player != NULL) {
 #define BEGIN_BROADCAST_EXCEPT(players, except) if(players->mc) pthread_rwlock_rdlock(&players->data_mutex); for (size_t i = 0; i < players->size; i++) {struct player* bc_player = (struct player*) players->data[i];if (bc_player != NULL && bc_player != except) {
 #define END_BROADCAST_MT(players) }} if(players->mc) pthread_rwlock_unlock(&players->data_mutex);
 #define END_BROADCAST }}
 */

#endif /* GAME_H_ */

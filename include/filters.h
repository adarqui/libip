#ifndef FILTERS_H
#define FILTERS_H

typedef struct
{
	int family;
	int index;
	int state;
	int unused_only;
	inet_prefix pfx;
	int flushed;
	char *flushb;
	int flushp;
	int flushe;
} filter_neigh_t;

typedef struct
{
	int ifindex;
	int family;
	int oneline;
	int showqueue;
	inet_prefix pfx;
	int scope, scopemask;
	int flags, flagmask;
	int up;
	char *label;
	int flushed;
	char *flushb;
	int flushp;
	int flushe;
	int group;
} filter_addr_t;


typedef struct filters {
	filter_neigh_t neigh;
	filter_addr_t addr;
} filters_t;

#endif

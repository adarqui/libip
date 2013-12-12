#ifndef IP_NEIGH_H
#define IP_NEIGH_H

typedef struct
{
	int family;
	int index;
	int state;
	int unused_only;
	net_prefix pfx;
	int flushed;
	char *flushb;
	int flushp;
	int flushe;
} filter_neigh_t;

#endif

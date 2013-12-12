#ifndef PARSE_H
#define PARSE_H

#include "libip.h"

typedef struct obj {

	struct rtnl_handle * rth;
	struct sockaddr_nl * who;
	struct nlmsghdr * n;
	void *js;

} obj_t;

#endif

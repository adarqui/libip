#ifndef IP_MONITOR_H
#define IP_MONITOR_H

typedef enum {
	IP_MONITOR_OPT_LINK = 0x0001,
	IP_MONITOR_OPT_ADDRESS = 0x0002,
	IP_MONITOR_OPT_ROUTE = 0x0004,
	IP_MONITOR_OPT_PREFIX = 0x0008,
	IP_MONITOR_OPT_NEIGH = 0x0010,
	IP_MONITOR_OPT_ALL = 0xFFffFFff
} monitor_flags_t;

/*
typedef struct monitor_event {
	struct sockaddr_nl * who;
	struct nlmsghdr * n;
} monitor_event_t;
*/

typedef int (* monitor_handler_t )(obj_t *);

typedef struct monitor_cmd {
	struct rtnl_handle rth;
	int family;
	int groups;
	monitor_flags_t flags;
	monitor_handler_t handler;
	filters_t filters;
} monitor_cmd_t;

int monitor_init(monitor_cmd_t *);
int monitor_setopt(monitor_cmd_t *, monitor_flags_t);

int monitor_accept_msg(struct sockaddr_nl *, struct nlmsghdr *, void *);

#endif

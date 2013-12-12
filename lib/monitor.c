#include "libip.h"

int monitor_accept_msg(struct sockaddr_nl *who,
	       struct nlmsghdr *n, void *arg)
{
	monitor_cmd_t * mon = (monitor_cmd_t *) arg;
	obj_t monev;

	puts("monitor_accept_message");

	if(!who || !n || !arg) return -1;

	monev.rth = &mon->rth;
	monev.who = who;
	monev.n = n;
	monev.js = NULL;

	printf("%p\n", mon->handler);
	mon->handler(&monev);
	return 0;
}

int monitor_init(monitor_cmd_t *mon) {
	if(!mon) return -1;

	memset(mon,0,sizeof(monitor_cmd_t));

	mon->groups = RTMGRP_TC;

	return 0;
}

int monitor_events(monitor_cmd_t *mon, monitor_handler_t fn) {
	if(!mon || !fn) return -1;

	if (rtnl_open(&mon->rth, mon->groups) < 0)
		return -1;

	ll_init_map(&mon->rth);

	mon->handler = fn;
	if (rtnl_listen(&mon->rth, monitor_accept_msg, mon) < 0)
		return -1;

	return 0;
}

int monitor_setopt(monitor_cmd_t *mon, monitor_flags_t flags)
{
	int llink=0;
	int laddr=0;
	int lroute=0;
	int lprefix=0;
	int lneigh=0;

	if(!mon) return -1;

	if(flags & IP_MONITOR_OPT_ALL) {
		llink = laddr = lroute = lprefix = lneigh = 1;
	}
	else {
		if(flags & IP_MONITOR_OPT_LINK) {
			llink = 1;
		}
		if(flags & IP_MONITOR_OPT_ADDRESS) {
			laddr = 1;
		}
		if(flags & IP_MONITOR_OPT_ROUTE) {
			lroute = 1;
		}
		if(flags & IP_MONITOR_OPT_PREFIX) {
			lprefix = 1;
		}
		if(flags & IP_MONITOR_OPT_NEIGH) {
			lneigh = 1;
		}
	}

	if (llink)
		mon->groups |= nl_mgrp(RTNLGRP_LINK);
	if (laddr) {
		if (!mon->family || mon->family == AF_INET)
			mon->groups |= nl_mgrp(RTNLGRP_IPV4_IFADDR);
		if (!mon->family || mon->family == AF_INET6)
			mon->groups |= nl_mgrp(RTNLGRP_IPV6_IFADDR);
	}
	if (lroute) {
		if (!mon->family || mon->family == AF_INET)
			mon->groups |= nl_mgrp(RTNLGRP_IPV4_ROUTE);
		if (!mon->family || mon->family == AF_INET6)
			mon->groups |= nl_mgrp(RTNLGRP_IPV6_ROUTE);
	}
	if (lprefix) {
		if (!mon->family || mon->family == AF_INET6)
			mon->groups |= nl_mgrp(RTNLGRP_IPV6_PREFIX);
	}
	if (lneigh) {
		mon->groups |= nl_mgrp(RTNLGRP_NEIGH);
	}

	return 0;
}

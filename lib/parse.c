#include "libip.h"

int parse_neigh(obj_t *obj) {
	if(!obj) return -1;

	puts("parse_neigh!");

	return 0;
}


int parse(obj_t *obj) {

	if(!obj) return -1;

	if (obj->n->nlmsg_type == RTM_NEWROUTE || obj->n->nlmsg_type == RTM_DELROUTE) {
//		print_route(who, n, arg);
	}
	else if (obj->n->nlmsg_type == RTM_NEWLINK || obj->n->nlmsg_type == RTM_DELLINK) {
		ll_remember_index(obj->who, obj->n, NULL);
//		print_linkinfo(who, n, arg);
	}
	else if (obj->n->nlmsg_type == RTM_NEWADDR || obj->n->nlmsg_type == RTM_DELADDR) {
//		print_addrinfo(who, n, arg);
	}
	else if (obj->n->nlmsg_type == RTM_NEWADDRLABEL || obj->n->nlmsg_type == RTM_DELADDRLABEL) {
//		print_addrlabel(who, n, arg);
	}
	else if (obj->n->nlmsg_type == RTM_NEWNEIGH || obj->n->nlmsg_type == RTM_DELNEIGH) {
		parse_neigh(obj);
	}
	else if (obj->n->nlmsg_type == RTM_NEWPREFIX) {
//		print_prefix(who, n, arg);
	}
	else if (obj->n->nlmsg_type == RTM_NEWRULE || obj->n->nlmsg_type == RTM_DELRULE) {
//		print_rule(who, n, arg);
	}
	else if (obj->n->nlmsg_type == 15) {
		char *tstr;
		time_t secs = ((__u32*)NLMSG_DATA(obj->n))[0];
		long usecs = ((__u32*)NLMSG_DATA(obj->n))[1];
		tstr = asctime(localtime(&secs));
		tstr[strlen(tstr)-1] = 0;
	}
	else if (obj->n->nlmsg_type == RTM_NEWQDISC ||
	    obj->n->nlmsg_type == RTM_DELQDISC ||
	    obj->n->nlmsg_type == RTM_NEWTCLASS ||
	    obj->n->nlmsg_type == RTM_DELTCLASS ||
	    obj->n->nlmsg_type == RTM_NEWTFILTER ||
	    obj->n->nlmsg_type == RTM_DELTFILTER)
	{ }
	else if (obj->n->nlmsg_type != NLMSG_ERROR && obj->n->nlmsg_type != NLMSG_NOOP &&
	    obj->n->nlmsg_type != NLMSG_DONE) {
	}

	return 0;
}

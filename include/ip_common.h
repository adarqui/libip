#ifndef IP_COMMON_H
#define IP_COMMON_H

extern int get_operstate(const char *name);
/*
extern int print_linkinfo(const struct sockaddr_nl *who,
			  struct nlmsghdr *n,
			  void *arg);
extern int print_addrinfo(const struct sockaddr_nl *who,
			  struct nlmsghdr *n,
			  void *arg);
extern int print_addrlabel(const struct sockaddr_nl *who,
			   struct nlmsghdr *n, void *arg);
extern int print_neigh(const struct sockaddr_nl *who,
		       struct nlmsghdr *n, void *arg);
extern int print_ntable(const struct sockaddr_nl *who,
			struct nlmsghdr *n, void *arg);
			*/
extern int ipaddr_list(int argc, char **argv);
extern int ipaddr_list_link(int argc, char **argv);
extern int iproute_monitor(int argc, char **argv);
extern void iplink_usage(void) __attribute__((noreturn));
extern void iproute_reset_filter(void);
extern void ipaddr_reset_filter(int);
extern void ipneigh_reset_filter(void);
extern void ipntable_reset_filter(void);
extern int print_route(const struct sockaddr_nl *who,
		       struct nlmsghdr *n, void *arg);
extern int print_prefix(const struct sockaddr_nl *who,
			struct nlmsghdr *n, void *arg);
extern int print_rule(const struct sockaddr_nl *who,
		      struct nlmsghdr *n, void *arg);

static inline int rtm_get_table(struct rtmsg *r, struct rtattr **tb)
{
	__u32 table = r->rtm_table;
	if (tb[RTA_TABLE])
		table = rta_getattr_u32(tb[RTA_TABLE]);
	return table;
}

struct link_util
{
	struct link_util	*next;
	const char		*id;
	int			maxattr;
	int			(*parse_opt)(struct link_util *, int, char **,
					     struct nlmsghdr *);
	void			(*print_opt)(struct link_util *, FILE *,
					     struct rtattr *[]);
	void			(*print_xstats)(struct link_util *, FILE *,
					     struct rtattr *);
};

struct link_util *get_link_kind(const char *kind);
int get_netns_fd(const char *name);

#ifndef	INFINITY_LIFE_TIME
#define     INFINITY_LIFE_TIME      0xFFFFFFFFU
#endif

#endif

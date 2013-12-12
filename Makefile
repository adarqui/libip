CC := gcc
CFLAGS := -Wall -O3 -fPIC
LDFLAGS := -shared
INCLUDE := -I ./include

NAME := ip
MAJOR := 0
MINOR := 1

VERSION = $(MAJOR).$(MINOR)

SRCS := lib/dnet_ntop.c lib/dnet_pton.c lib/ipx_ntop.c lib/ipx_pton.c lib/libnetlink.c lib/utils.c lib/ll_addr.c lib/ll_map.c lib/ll_proto.c lib/ll_types.c lib/monitor.c lib/parse.c

OBJS := $(SRCS:.c=.o)


lib: lib$(NAME).so.$(VERSION)

lib$(NAME).so.$(VERSION): $(SRCS)
	$(CC) $(INCLUDE) $(LDFLAGS) $(CFLAGS) -Wl,-soname,lib$(NAME).so.$(MAJOR) $^ -o $@
	ln -s lib$(NAME).so.$(VERSION) lib$(NAME).so.$(MAJOR)

clean:
	rm -f *.o *.so *.0 lib$(NAME).so.$(VERSION)

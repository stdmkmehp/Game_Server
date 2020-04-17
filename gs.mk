CC = gcc
RM = rm -f
AR = ar

GS_HOME = /home/zw/workspace/game_server
GS_INC = $(GS_HOME)/include
GS_LIB = $(GS_HOME)/lib
GS_BIN = $(GS_HOME)/bin

# CINC = -I$(TSF4G_INC)/ ${TSF4G_DBMS_INCLUDE}

# LDPATH += -L/usr/lib/x86_64-linux-gnu -Llib -lgcov -ftest-coverage -fprofile-arcs -lm -lstdc++ -Llib -lgcov -ftest-coverage -fprofile-arcs -lm -lrt -lanl
# LDPATH += $(mysql_config --libs)
# LDPATH += -L/usr/lib/ -L/usr/local/lib
# LDPATH += -L$(GS_LIB)/

LIBS += -lstdc++
# LIBS += -lnsl -lpthread -ldl

SHARED = -shared -z defs

CFLAGS = -g -pg --std=c++11
# CFLAGS += -I/usr/include/mysql
# CFLAGS += -D_NEW_LIC -D_GNU_SOURCE -D_REENTRANT
CFLAGS += -Wall -Wextra -pipe -fPIC
# CFLAGS += -I$(GS_INC)
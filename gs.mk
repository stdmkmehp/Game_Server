CC = gcc --std=c++11
RM = rm -f
AR = ar

# GS_INC = /home/zw/workspace/game_server/include/
# GS_LIB = /home/zw/workspace/game_server/lib/

# CINC = -I$(TSF4G_INC)/ ${TSF4G_DBMS_INCLUDE}

# LDPATH += -L/usr/lib/x86_64-linux-gnu -Llib -lgcov -ftest-coverage -fprofile-arcs -lm -lstdc++ -Llib -lgcov -ftest-coverage -fprofile-arcs -lm -lrt -lanl
# LDPATH += $(mysql_config --libs)
# LDPATH += -L/usr/lib/ -L/usr/local/lib
# LDPATH += -L$(GS_LIB)/

# LIBS = -lnsl -lpthread -ldl

SHARED = -shared -z defs

CFLAGS = -g -pg
# CFLAGS += -I/usr/include/mysql
# CFLAGS += -D_NEW_LIC -D_GNU_SOURCE -D_REENTRANT
CFLAGS += -Wall -Wextra -pipe -fPIC
# CFLAGS += -I$(GS_INC)
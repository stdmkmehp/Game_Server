# $<第一个依赖文件 $@目标文件 $^所有的依赖文件
include ../../gs.mk

TASK_CPPFILE = $(wildcard *.cpp)
TASK_OBJ = $(TASK_CPPFILE:.cpp=.o)
TASK_BIN = echoserver

CFLAGS += -I../../include
# LIBS = $(LDPATH) $(TSF4G_LIB)/libtsf4g.a  -lrt   -Wl,-Bstatic -lscew  -lexpat -Wl,-Bdynamic -lpthread
LIBS += -L/home/zw/workspace/game_server/src/conn/ -static -lconn
LIBS += -L/usr/lib/ -L/usr/local/lib
LIBS += -L/usr/lib/x86_64-linux-gnu -Llib -lgcov -ftest-coverage -fprofile-arcs -lm -lstdc++ -Llib -lgcov -ftest-coverage -fprofile-arcs -lm -lrt -lanl

.PHONY: all clean

all: $(TASK_BIN)

-include $(TASK_CPPFILE:.cpp=.d)

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -o $@

%.o: %.cpp %.d
	$(CC) -c $(CFLAGS) $<


$(TASK_BIN): $(TASK_OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	$(RM) *.o  *.d
	$(RM) $(TASK_BIN)

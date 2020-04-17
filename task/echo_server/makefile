# $<第一个依赖文件 $@目标文件 $^所有的依赖文件
include ../../gs.mk

TASK_BIN = echoserver echoclient
TASK_BIN_DIR = $(GS_BIN)
TASK_CPPFILE = $(wildcard *.cpp)

CFLAGS += -I$(GS_INC)
LIBS += -L$(GS_LIB) -lconn -lstdc++ -Wl,-rpath=$(GS_LIB)

.PHONY: all clean

all: $(TASK_BIN)
	mkdir -p $(TASK_BIN_DIR)
	cp $(TASK_BIN) $(TASK_BIN_DIR)

-include $(TASK_CPPFILE:.cpp=.d)

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -o $@

%.o: %.cpp %.d
	$(CC) -c $(CFLAGS) $<

$(TASK_BIN):%:%.o
	$(CC) -o $@ $(CFLAGS) $< $(LIBS)

clean:
	$(RM) *.o  *.d
	$(RM) $(TASK_BIN)

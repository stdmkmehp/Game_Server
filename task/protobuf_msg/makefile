# $<第一个依赖文件 $@目标文件 $^所有的依赖文件
include ../../gs.mk

TASK_BIN = protobuf_server protobuf_client
TASK_BIN_DIR = $(GS_BIN)
TASK_CPPFILE = $(wildcard *.cpp)
PROTOBUF_CCFILE = $(wildcard *.cc)

CFLAGS += -I$(GS_INC) -I/usr/local/include
LIBS += -pthread -L/usr/local/lib -lprotobuf
LIBS += -L$(GS_LIB) -lconn -lstdc++ -Wl,-rpath=$(GS_LIB)

.PHONY: all clean

all: $(TASK_BIN)
	mkdir -p $(TASK_BIN_DIR)
	cp $(TASK_BIN) $(TASK_BIN_DIR)

-include $(TASK_CPPFILE:.cpp=.d) $(PROTOBUF_CCFILE:.cc=.d) 

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -o $@
%.o: %.cpp %.d
	$(CC) -c $(CFLAGS) $<

%.d: %.cc
	$(CC) -MM $(CFLAGS) $< -o $@
%.o: %.cc %.d
	$(CC) -c $(CFLAGS) $<

$(TASK_BIN):%:%.o $(PROTOBUF_CCFILE:.cc=.o)
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	$(RM) *.o  *.d
	$(RM) $(TASK_BIN)

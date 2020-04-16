# $<第一个依赖文件 $@目标文件 $^所有的依赖文件
include ../../gs.mk

TASK_CPPFILE = $(wildcard *.cpp)
TASK_OBJ = $(TASK_CPPFILE:.cpp=.o)
TASK_LIB = libconn.a

CFLAGS += -I../../include
# LIBS = $(LDPATH) $(TSF4G_LIB)/libtsf4g.a  -lrt   -Wl,-Bstatic -lscew  -lexpat -Wl,-Bdynamic -lpthread

.PHONY: all clean

all: $(TASK_LIB)

-include $(TASK_CPPFILE:.cpp=.d)

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -o $@

%.o: %.cpp %.d
	$(CC) -c $(CFLAGS) $<


$(TASK_LIB): $(TASK_OBJ)
	${AR} cr $@ $^

clean:
	$(RM) *.o  *.d
	$(RM) $(TASK_LIB)

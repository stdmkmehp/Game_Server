# $<第一个依赖文件 $@目标文件 $^所有的依赖文件
include ../../gs.mk

TASK_STATIC_LIB = libconn.a
TASK_SHARED_LIB = libconn.so
TASK_CPPFILE = $(wildcard *.cpp)
TASK_OBJ = $(TASK_CPPFILE:.cpp=.o)
TASK_LIB_DIR = $(GS_LIB)

CFLAGS += -I$(GS_INC)

.PHONY: all clean

all: $(TASK_SHARED_LIB) #$(TASK_STATIC_LIB)
	mkdir -p $(TASK_LIB_DIR)
	cp $(TASK_SHARED_LIB) $(TASK_LIB_DIR)
	# cp $(TASK_STATIC_LIB) $(TASK_LIB_DIR)

-include $(TASK_CPPFILE:.cpp=.d)

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< -o $@

%.o: %.cpp %.d
	$(CC) -c $(CFLAGS) $<

$(TASK_STATIC_LIB): $(TASK_OBJ)
	${AR} cr $@ $^

$(TASK_SHARED_LIB): $(TASK_OBJ)
	$(CC) $(SHARED) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	$(RM) *.o  *.d
	$(RM) $(TASK_SHARED_LIB) $(TASK_STATIC_LIB)

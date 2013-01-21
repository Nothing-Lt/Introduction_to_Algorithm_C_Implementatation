# change the "target" to your real target use M-% or C-M-%
# add the c files used in SRCS
CC = gcc
OFLAG = -o 
CFLAGS = -Wall -g
SRCS = bfs_test.c include/require.c queue.c adj_table.c bfs.c
DEPS := $(SRCS:.c=.d)

# �˴�Ϊ�����ĸ߼��÷�����SRCS�����е�.c�ļ����.o�ļ�������Ϊ����OBJECTS
OBJECTS := $(SRCS:.c=.o)

ifdef SystemRoot
   RM = del /Q
   FixPath = $(subst /,\,$1)
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      FixPath = $1
   endif
endif

all: bfs_test

-include $(DEPS)
%.o:%.c
	$(CC) $(CFLAGS) -c -MMD $< -o $@

# specify the header files dependency here
# using the gcc -MM source.c option
bfs_test: ${OBJECTS}
	${CC} $^ ${OFLAG} $@

.PHONY:clean
# ע��call ����ı��ʽ���ü�$����
clean:
	$(RM) $(call FixPath, ${OBJECTS} ${DEPS})

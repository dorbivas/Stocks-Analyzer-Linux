
NAMES = stockData best_pe csvExport 
PROGRAMS = $(NAMES:%=%.out)

IDIR = .
SO = libutils.so

CLEAN = $(PROGRAMS) $(OBJS) $(SO)
CC = g++
CFLAGS = -I$(IDIR) -Wall

#SRCS := $(subst ./,,$(shell find . -maxdepth 1 -name "*.cpp"))
OBJS = $(NAMES:%=%.o) $(SO:%.so=%.o)

utils.o: CFLAGS += -fPIC
all: $(SO) $(PROGRAMS) 

lib%.so: %.o
	$(CC) -o $@ $^ -shared $(CFLAGS) -fPIC

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) 

$(PROGRAMS): %.out: %.o 
	$(CC) -o $@ $^ $(CFLAGS) -L. -lutils 

$(OBJS): %.o: %.h 

.PHONY: clean
clean:
	rm -f $(CLEAN) 

SRCS = $(NAMES:%=%.cpp) $(NAMES:%=%.h) utils.cpp utils.h Makefile get_stock_data.sh readMe.txt
	
.PHONY: pack
pack:
	project.zip

project.zip: $(SRCS)
	zip $@ $^


CC = gcc
CXX = g++

#CFLAGS = -O2 -fopenmp
CFLAGS = -g
CFLAGS += -Wall -Wno-parentheses

CPPFLAGS = $(CFLAGS) -std=c++11
CPPFLAGS += -DBOOST_LOG_DYN_LINK
CPPFLAGS += `pkg-config opencv4 --cflags`

LDFLAGS += `pkg-config opencv4 --libs`
LDFLAGS += -L/usr/local/Cellar/boost/1.70.0/lib
LDFLAGS += -lboost_system -lboost_program_options
LDFLAGS += -lboost_log -lboost_log_setup -lboost_log-mt

CSRCS =
CPPSRCS = main.cpp geometry.cpp

OBJS = $(CSRCS:.c=.o) $(CPPSRCS:.cpp=.o)

TARGET = a.out

.PHONY: depend clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -v -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $<

%.s: %.cpp
	$(CXX) $(CPPFLAGS) -S -o $@ -c $<

clean:
	$(RM) $(OBJS) $(EXTRA) $(TARGET)

distclean: clean
	$(RM) *~ .depend

depend: .depend

.depend: $(CSRCS) $(CPPSRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^ >> ./.depend

include .depend

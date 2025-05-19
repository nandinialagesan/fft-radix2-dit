CC = gcc
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lm

SRCS = src/fft.c src/fft_optimized.c main.c benchmark.c
OBJS = src/fft.o src/fft_optimized.o main.o benchmark.o

TARGET = fft
PERF_TARGET = fft_perf

.PHONY: all perf clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

perf:
	$(CC) $(CFLAGS) -fno-omit-frame-pointer -o $(PERF_TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f main.o benchmark.o src/fft.o src/fft_optimized.o $(TARGET) $(PERF_TARGET) time_domain_signal.txt perf.data


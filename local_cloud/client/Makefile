TARGET = local_cloud_client.out

CXX = g++ -std=c++20 -O3

SOURCES = main.cpp cloud_client.cpp

LDFLAGS = -lboost_system -lboost_thread

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(LDFLAGS) -o $@

clean:
	rm -f $(TARGET)

install:
	cp $(TARGET) /usr/local/bin/

run:
	./$(TARGET)

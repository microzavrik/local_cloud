TARGET= local_cloud_server.out

CXX = g++ -std=c++17 -O3

SOURCES = main.cpp cloud_client.cpp get_file_size_in_bytes.hpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(LDFLAGS) -o $@

clean:
	rm -f $(TARGET)

install:
	cp $(TARGET) /usr/local/bin/

run:
	./$(TARGET) 

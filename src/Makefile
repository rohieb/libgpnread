OBJS := main.o master_data.o utils.o
TARGET := libgpnread.so

CXXFLAGS = -fPIC

all: $(TARGET)

# pull in dependency info for *existing* .o files
-include $(patsubst %.o,deps/%.d,$(OBJS))

$(TARGET): $(OBJS)
	gcc -shared -o $@ $^

deps/%.d: %.cpp
	@mkdir -p deps
	@g++ -MM $(CXXFLAGS) $< > $@.tmp
	@sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@
	@rm -f $@.tmp

%.o: deps/%.d
	g++ -c $(CXXFLAGS) $*.cpp -o $*.o

clean:
	rm -rf $(TARGET) *.o deps/


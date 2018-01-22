all: pigpio_lite

pigpio_lite: download copy_include
	cd src && $(MAKE)

download:
	wget https://github.com/joan2937/pigpio/archive/master.zip
	unzip master.zip
	mv pigpio-master src
	rm -f master.zip

copy_include:
	mkdir -p include/pigpio_lite
	cp src/*.h include/pigpio_lite

install:
	cd src && make install


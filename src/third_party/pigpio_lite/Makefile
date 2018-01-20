all: pigpio

pigpio: download copy_include
	cd src && $(MAKE)

download:
	wget https://github.com/joan2937/pigpio/archive/master.zip
	unzip master.zip
	mv pigpio-master src
	rm -f master.zip

copy_include:
	mkdir -p include/pigpio
	cp src/*.h include/pigpio

install:
	cd src && make install


all: pigpio

pigpio:
	wget https://github.com/joan2937/pigpio/archive/master.zip
	unzip master.zip
	mv pigpio-master src
	rm -f master.zip
	cd src && make && make install
	mkdir -p include/pigpio
	cp src/pigpio.h include/pigpio/pigpio.h
	chown -R pi:pi include/pigpio/pigpio.h
	chown -R pi:pi include/pigpio
	chown -R pi:pi include

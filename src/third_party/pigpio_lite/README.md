# Pigpio

## Installing `pigpio`

The following downloads the [`pigpio`](http://abyz.me.uk/rpi/pigpio/) source and installs it to the system. It also copies header files to `include/pigpio`. This allows use of the [`pigpiod` C interface](http://abyz.me.uk/rpi/pigpio/pdif2.html) (_not_ the standard `pigpio` C interface).

```bash
$ make
$ sudo make install
```

## Using `pigpio_lite` in a C++ ROS package

1. Add the following to your `package.xml`

```xml
<depend>pigpio_lite</depend>
```

2. Add the following to your `CMakeLists.txt`

```cmake
find_package(catkin REQUIRED COMPONENTS pigpio_lite)
find_package(Threads REQUIRED)

catkin_package(
    CATKIN_DEPENDS pigpio_lite
    DEPENDS pigpio
)

include_directories(include ${catkin_INCLUDE_DIRS})

# For any targets, link pigpiod_if2 and pthread
target_link_libraries(target
    pigpiod_if2
    ${CMAKE_THREAD_LIBS_INIT}
)
```

3. Import `<pigpio_lite/pigpiod_if2.h>` in C++ files that use `pigpio`

```c++
#include <pigpio_lite/pigpiod_if2.h>

...

int pi = pigpio_start(nullptr, nullptr);
```

4. Use the [`pigpiod` C interface](http://abyz.me.uk/rpi/pigpio/pdif2.html) to control GPIO pins.

## Note about `pigpio` vs `pigpiod` C interface

For ROS, the simplest way to use `pigpio` is with the `pigpiod` (daemon) interface. The reason for this is that access to the GPIO pins (at least in the way `pigpio` has implemented it) requires `sudo` privileges. That is, in order to run a C++ file that hooks into the standard `pigpio` C interface, it has to be done with `sudo`. This practice is discouraged for ROS executables (and `sudo rosrun ...` often doesn't work anyway).

Fortunately, the `pigpiod` interface has the same capabilities as the standard interface; it just requires a few extra pieces of boilerplate.

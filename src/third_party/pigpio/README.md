# Pigpio

## Callback function signature:

Unfortunately, porting `pigpio` to C++ required making some changes to how callbacks are constructed. If you are creating a callback, it must use the following signature, no matter what:

```c++
void (*callback) (int, int, uint32_t, void*)
```

## Installing `pigpio`

The following downloads the [`pigpio`](http://abyz.me.uk/rpi/pigpio/) source and installs it to the system. It also copies header files to `include/pigpio`. This allows use of the [`pigpiod` C interface](http://abyz.me.uk/rpi/pigpio/pdif2.html) (_not_ the standard `pigpio` C interface).

```bash
$ make
$ sudo make install
```

## Using `pigpio` in a C++ ROS package

1. Add the following to your `package.xml`

```xml
<depend>pigpio</depend>
```

2. Add the following to your `CMakeLists.txt`

```cmake
find_package(catkin REQUIRED COMPONENTS pigpio)
find_package(Threads REQUIRED)

catkin_package(
    CATKIN_DEPENDS pigpio
    DEPENDS pigpio
)

include_directories(include ${catkin_INCLUDE_DIRS})

# For any targets, link pigpiod_if2 and pthread
target_link_libraries(target
    pigpiod_if2
    ${CMAKE_THREAD_LIBS_INIT}
)
```

3. Import `<pigpio/pigpiod_if2.h>` in C++ files that use `pigpio`

```c++
#include <pigpio/pigpiod_if2.h>

...

int pi = pigpio_start(nullptr, nullptr);
```

4. Use the [`pigpiod` C interface](http://abyz.me.uk/rpi/pigpio/pdif2.html) to control GPIO pins.

## Note about `pigpio` vs `pigpiod` C interface

For ROS, the simplest way to use `pigpio` is with the `pigpiod` (daemon) interface. The reason for this is that access to the GPIO pins (at least in the way `pigpio` has implemented it) requires `sudo` privileges. That is, in order to run a C++ file that hooks into the standard `pigpio` C interface, it has to be done with `sudo`. This practice is discouraged for ROS executables (and `sudo rosrun ...` often doesn't work anyway).

Fortunately, the `pigpiod` interface has the same capabilities as the standard interface; it just requires a few extra pieces of boilerplate.

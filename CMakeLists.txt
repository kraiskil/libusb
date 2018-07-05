#Note: this CMake build script is not part of the
#"official" libusbx source package. It is added
#for convenience if you want to include this library in
#your CMake project. No testing/guarantee this script
#will build a (working) libusb              -kra
project(libusb C)
#This CMake file is developed with CMake 3.5, which imposes
#the restriction vesrsion>2.4. No other reason yet
cmake_minimum_required(VERSION 2.5)


set(COMMON_SRC
	libusb/core.c
	libusb/descriptor.c
	libusb/hotplug.c
	libusb/io.c
	libusb/strerror.c
	libusb/sync.c
)
include_directories(libusb)

#Platform dependent stuff
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(PLATFORM_SRC
		libusb/os/linux_usbfs.c
		libusb/os/poll_posix.c
		libusb/os/threads_posix.c)
	include_directories(linux)
	add_definitions(-Wall -Werror)
endif()


add_library(libusb SHARED
	${COMMON_SRC}
	${PLATFORM_SRC})

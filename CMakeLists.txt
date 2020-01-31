#Note: this CMake build script is not part of the
#"official" libusbx source package. It is added
#for convenience if you want to include this library in
#your CMake project. No testing/guarantee this script
#will build a (working) libusb              -kra
project(libusb C)
#This CMake file is developed with CMake 3.5, which imposes
#the restriction vesrsion>2.4. No other reason yet
cmake_minimum_required(VERSION 2.5)

option(INSTALL_LIBUSB "Install libUSB library." ON)

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
		libusb/os/linux_netlink.c
		libusb/os/poll_posix.c
		libusb/os/threads_posix.c)
	include_directories(linux)
	add_definitions(-Wall -Werror)
	add_definitions(-fPIC)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(PLATFORM_SRC
		libusb/os/poll_windows.c
		libusb/os/threads_windows.c
		libusb/os/windows_nt_common.c
		libusb/os/windows_usbdk.c
		libusb/os/windows_winusb.c)
	include_directories(msvc)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(PLATFORM_SRC
		libusb/os/darwin_usb.c
		libusb/os/poll_posix.c
		libusb/os/threads_posix.c)
	include_directories(Xcode)
	set(PLATFORM_LIB
		"-framework CoreFoundation"
		"-framework IOKit")
endif()


add_library(usb SHARED
	${COMMON_SRC}
	${PLATFORM_SRC})
target_link_libraries(usb ${PLATFORM_LIB})
target_include_directories(usb
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libusb>
	)

if( INSTALL_LIBUSB )
	install(
		TARGETS usb
		DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

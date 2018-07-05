/* The Autotools buildsystem creates a config.h file
 * which is included all over the sources. 
 * This file fakes that for a CMake build on a Linux host.
 */
#pragma once

#define OS_LINUX
#define HAVE_POLL_H
#define HAVE_SYS_TIME_H
#define POLL_NFDS_TYPE nfds_t
#define THREADS_POSIX
#define DEFAULT_VISIBILITY __attribute__((visibility("default")))



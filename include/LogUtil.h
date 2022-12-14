#ifndef _LOG_UTILS_H_
#define _LOG_UTILS_H_

#include <stdio.h>
#include <string.h>

/**
 * A very simple logger
 * Example of utilisation :
 * LOGD("hello world");
 * LOGD("%d", 10);
 * -> [main.cpp][main][5]: hello world
 * -> [main.cpp][main][6]: 10
 *
 * Source : https://blog.csdn.net/afei__/article/details/82682857
 */

// #define __DEBUG__ // if u don't want debug log, comment this line
#define __INFO__

#define __FILENAME__ (strrchr(__FILE__, '/') + 1)

#ifdef __DEBUG__
#define LOG_DEBUG(format, ...)                                                 \
  printf("[DEBUG][%s][%s][%d]: " format "\n", __FILENAME__, __FUNCTION__,      \
         __LINE__, ##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...)                                       
  
#endif

#ifdef __INFO__
#define LOG_INFO(format, ...)                                                  \
  printf("[INFO][%s][%s][%d]: " format "\n", __FILENAME__, __FUNCTION__,       \
         __LINE__, ##__VA_ARGS__)

// #define LOG_INFO(format, ...)
#endif




#endif // _LOG_UTILS_H_
#ifndef _ERRMSG_H_
#define _ERRMSG_H_

#define errmsg(fmt, ...) \
	fprintf(stderr, "[libcweather ERROR] " fmt "\n", ##__VA_ARGS__)

#endif /* _ERRMSG_H_ */

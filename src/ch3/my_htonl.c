#include <stdint.h>
#include <netinet/in.h>

uint32_t htonl(uint32_t x)
{
#if BYTE_ORDER == BIG_ENDIAN
	return x;
#elif BYTE_ORDER == LITTLE_ENDIAN
	return __bswap_32(x);
#else
# error "What kind of system is this?"
#endif
}
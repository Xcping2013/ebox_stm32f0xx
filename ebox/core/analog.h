#ifndef __ANALOG_H
#define __ANALOG_H

#include "common.h"

extern void ADC1_init(uint32_t CH, GPIO *pin);
extern uint16_t analogin_read(uint32_t *CH);

class Analog{

public:

    /** Create an AnalogIn, connected to the specified pin
     *
     * @param pin AnalogIn pin to connect to
     * @param name (optional) A string to identify the object
     */
    Analog(GPIO *pin) {
		pin->mode(AIN);
	switch (pin->pin)
	{
	case LL_GPIO_PIN_0:
		Channel = LL_ADC_CHANNEL_0 ;
		break;
	case LL_GPIO_PIN_1:
		Channel = LL_ADC_CHANNEL_1 ;
		break;
	case LL_GPIO_PIN_2:
		Channel = LL_ADC_CHANNEL_2 ;
		break;
	case LL_GPIO_PIN_3:
		Channel = LL_ADC_CHANNEL_3 ;
		break;
	default:
		break;
	}
        ADC1_init( Channel, pin);
    }

    /** Read the input voltage, represented as a float in the range [0.0, 1.0]
     *
     * @returns A floating-point value representing the current input voltage, measured as a percentage
     */
    float read() {
        return (float)analogin_read( &Channel);
    }

    /** Read the input voltage, represented as an unsigned short in the range [0x0, 0xFFFF]
     *
     * @returns
     *   16-bit unsigned short representing the current input voltage, normalised to a 16-bit value
     */
    unsigned short read_u16() {
        // return analogin_read_u16(&_adc);
      return 0;
    }

private:
	uint32_t Channel;	
};

#endif

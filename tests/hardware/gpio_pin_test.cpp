#include <cassert>
#include <iostream>

#include "hardware/gpio_pin.hpp"

int main()
{
	// Création en OUTPUT
	GpioPin led(GpioPin::OUTPUT);

	assert(led.mode() == GpioPin::OUTPUT);
	assert(led.read() == GpioPin::LOW);

	// write HIGH
	led.write(GpioPin::HIGH);
	assert(led.read() == GpioPin::HIGH);

	// write LOW
	led.write(GpioPin::LOW);
	assert(led.read() == GpioPin::LOW);

	// Changement de mode
	led.setMode(GpioPin::INPUT);
	assert(led.mode() == GpioPin::INPUT);

	// write en INPUT ne doit rien changer
	led.write(GpioPin::HIGH);
	assert(led.read() == GpioPin::LOW);

	// Retour en OUTPUT
	led.setMode(GpioPin::OUTPUT);
	assert(led.mode() == GpioPin::OUTPUT);

	// On peut à nouveau écrire
	led.write(GpioPin::HIGH);
	assert(led.read() == GpioPin::HIGH);

	std::cout << "GpioPin tests passed." << std::endl;

	return 0;
}

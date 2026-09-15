#include "gpio_pin.hpp"

GpioPin::GpioPin(GpioPin::Mode mode)
{
	this->mode_ = mode;
	this->state_ = LOW;
}

void GpioPin::setMode(GpioPin::Mode mode)
{
	this->mode_ = mode;
}

void GpioPin::write(GpioPin::State state)
{
	if(this->mode_ == GpioPin::INPUT)
		return;

	this->state_ = state;
}

GpioPin::State GpioPin::read() const
{
	return this->state_;
}

GpioPin::Mode GpioPin::mode() const
{
	return this->mode_;
}

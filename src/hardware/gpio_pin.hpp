#pragma once

#include <cstdint>

class GpioPin {
	public:

		enum Mode
		{
			INPUT,
			OUTPUT
		};

		enum State
		{
			LOW,
			HIGH
		};

		GpioPin(Mode mode);

		void setMode(Mode mode);

		void write(State state);
		State read() const;

		Mode mode() const;

	private:
		Mode mode_;
		State state_;
};

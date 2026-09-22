#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include "uart.hpp"

static speed_t get_baudrate(uint32_t baudrate)
{
    switch (baudrate)
    {
        case 9600:
            return B9600;

        case 19200:
            return B19200;

        case 38400:
            return B38400;

        case 57600:
            return B57600;

        case 115200:
            return B115200;

        default:
            return 0;
    }
}

Uart::Uart(const std::string& device, uint32_t baudrate)
    : fd_(-1)
{
	// Ouverture du périphérique
    fd_ = open(device.c_str(), O_RDWR | O_NOCTTY);

    if (fd_ < 0)
    {
        return;
    }

	// Configuration d'un terminal/périphérique série.
    termios tty{};

	// Récupération de la config actuelle.
    if (tcgetattr(fd_, &tty) != 0)
    {
        close(fd_);
        fd_ = -1;
        return;
    }

	speed_t speed = get_baudrate(baudrate);

	if (speed == 0)
	{
		close(fd_);
		fd_ = -1;
		return;
	}

	// Vitesse de réception et émission.
	cfsetispeed(&tty, speed);
	cfsetospeed(&tty, speed);

    tty.c_cflag &= ~PARENB;   // Pas de bit de parité
    tty.c_cflag &= ~CSTOPB;   // 1 bit de stop
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;       // 8 bits de données

    tty.c_cflag |= CREAD | CLOCAL; // Autoriser la réception

	// ICANON ferait fonctionner le terminal comme une saisie utilisateur classique.
	// ECHO les caractères reçus ne sont pas automatiquement réaffichés.
	// ECHOE désactive le comportement d'effacement associé à l'écho.
	// ISIG les caractères spéciaux ne sont pas interprétés comme des signaux du terminal.
	// Le but est d'avoir un flux brut pas un terminal intéractif.
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	// Désactivation du flux logiciel.
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

	// Désactivation du traitement en sortie.
    tty.c_oflag &= ~OPOST;

	// Configuration de la lecture
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 0;

	// Application du paramétrage.
    if (tcsetattr(fd_, TCSANOW, &tty) != 0)
    {
        close(fd_);
        fd_ = -1;
        return;
    }
}

Uart::~Uart()
{
    if (fd_ >= 0)
    {
        close(fd_);
    }
}

bool Uart::send(uint8_t value)
{
    if (fd_ < 0)
    {
        return false;
    }

    return write(fd_, &value, 1) == 1;
}

bool Uart::send(const std::string& data)
{
    if (fd_ < 0)
    {
        return false;
    }

    return write(fd_, data.data(), data.size()) ==
           static_cast<ssize_t>(data.size());
}

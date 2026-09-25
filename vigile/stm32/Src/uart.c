/*
 * uart.c
 *
 *  Created on: 18 sept. 2026
 *      Author: angmnz
 */


#include "uart.h"
#include "stm32g071xx.h"

void uart_init(void)
{
    // Activer l'horloge de GPIOA
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

    // Activer l'horloge de USART2
	RCC->APBENR1 |= RCC_APBENR1_USART2EN;

    // PA2 et PA3 en Alternate Function (10)
    GPIOA->MODER &= ~GPIO_MODER_MODE2;
    GPIOA->MODER |= GPIO_MODER_MODE2_1;

    GPIOA->MODER &= ~GPIO_MODER_MODE3;
    GPIOA->MODER |= GPIO_MODER_MODE3_1;

    // AF1 -> USART2_TX (envois de données)
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2;
    GPIOA->AFR[0] |= (1U << GPIO_AFRL_AFSEL2_Pos);

    // AF1 -> USART2_RX (réception de données)
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3;
    GPIOA->AFR[0] |= (1U << GPIO_AFRL_AFSEL3_Pos);

    // Configurer le baud rate à 115200 bauds (baud rate = 16 000 000 Hz / 115 200 baud = 139)
    USART2->BRR = 139;

    // Activer l'émetteur, le récepteur et USART2
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void uart_send_char(char c)
{
    // Attendre que le registre de transmission soit disponible
	// (ISR = indicateur d'état et TXE_TXFNF =indique que le registre de transmission peut recevoir une nouvelle donnée)
    while ((USART2->ISR & USART_ISR_TXE_TXFNF) == 0)
    {
    }

    // Écrire le caractère à transmettre
    // (TDR = registre dans lequel on écrit le caractère à envoyer)
    USART2->TDR = c;
}

void uart_send_string(const char *str)
{
    while (*str != '\0')
    {
        uart_send_char(*str);
        str++;
    }
}

char uart_receive_char(void)
{
    // Attendre qu'un caractère soit reçu
    while ((USART2->ISR & USART_ISR_RXNE_RXFNE) == 0)
    {
    }

    // Lire le caractère reçu
    // (RDR = registre pour lire ce qui est reçu
    return (char)USART2->RDR;
}

void uart_receive_string(char *buffer, uint32_t size)
{
    uint32_t i = 0;

    while (i < size - 1)
    {
        char c = uart_receive_char();

        if (c == '\n' || c == '\r')
        {
            break;
        }

        buffer[i] = c;
        i++;
    }

    buffer[i] = '\0';
}






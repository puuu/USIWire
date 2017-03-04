// This file has been prepared for Doxygen automatic documentation generation.
/*! \file ********************************************************************
 *
 * Atmel Corporation
 *
 * File              : USI_TWI_Slave.h
 * Compiler          : IAR EWAAVR 4.11A
 * Revision          : $Revision: 6351 $
 * Date              : $Date: 2010-01-29 20:15:43 +0800 (Fri, 29 Jan 2010) $
 * Updated by        : $Author: hskinnemoen $
 *
 * Support mail      : avr@atmel.com
 *
 * Supported devices : All device with USI module can be used.
 *                     The example is written for the ATmega169, ATtiny26 & ATtiny2313
 *
 * AppNote           : AVR312 - Using the USI module as a TWI slave
 *
 * Description       : Header file for USI_TWI driver
 *
 *
 *
 ****************************************************************************/
//********** Prototypes **********//

void          USI_TWI_Slave_Initialise(unsigned char);
void          USI_TWI_Transmit_Byte(unsigned char);
unsigned char USI_TWI_Receive_Byte(void);
unsigned char USI_TWI_Data_In_Receive_Buffer(void);

void (*USI_TWI_On_Slave_Transmit)(void);
void (*USI_TWI_On_Slave_Receive)(int);

void Timer_Init(void);

#define TRUE 1
#define FALSE 0

typedef unsigned char uint8_t;

//////////////////////////////////////////////////////////////////
///////////////// Driver Buffer Definitions //////////////////////
//////////////////////////////////////////////////////////////////
// 1,2,4,8,16,32,64,128 or 256 bytes are allowed buffer sizes

#define TWI_RX_BUFFER_SIZE (16)
#define TWI_RX_BUFFER_MASK (TWI_RX_BUFFER_SIZE - 1)

#if (TWI_RX_BUFFER_SIZE & TWI_RX_BUFFER_MASK)
#error TWI RX buffer size is not a power of 2
#endif

// 1,2,4,8,16,32,64,128 or 256 bytes are allowed buffer sizes

#define TWI_TX_BUFFER_SIZE (16)
#define TWI_TX_BUFFER_MASK (TWI_TX_BUFFER_SIZE - 1)

#if (TWI_TX_BUFFER_SIZE & TWI_TX_BUFFER_MASK)
#error TWI TX buffer size is not a power of 2
#endif
//////////////////////////////////////////////////////////////////

#define USI_SLAVE_CHECK_ADDRESS (0x00)
#define USI_SLAVE_SEND_DATA (0x01)
#define USI_SLAVE_REQUEST_REPLY_FROM_SEND_DATA (0x02)
#define USI_SLAVE_CHECK_REPLY_FROM_SEND_DATA (0x03)
#define USI_SLAVE_REQUEST_DATA (0x04)
#define USI_SLAVE_GET_DATA_AND_SEND_ACK (0x05)

// Device dependant defines
#if defined(__AT90tiny26__) | defined(__ATtiny26__)
#define DDR_USI DDRB
#define PORT_USI PORTB
#define PIN_USI PINB
#define PORT_USI_SDA PORTB0
#define PORT_USI_SCL PORTB2
#define PIN_USI_SDA PINB0
#define PIN_USI_SCL PINB2
#define USI_START_COND_INT USISIF
#define TIMER_INT_MASK_REG TIMSK
#define OUTPUT_COMPARE_REG OCR1A
#define TIMER_CONTROL_REG TCCR1B
#define CLK_SELECT_PRESC_8 CS12
#define OUTPUT_COMP_INT_EN OCIE1A
#define USI_START_VECTOR USI_STRT_vect
#define USI_OVERFLOW_VECTOR USI_OVF_vect
#define TIMER_COMP_VECTOR TIMER0_COMP_vect
#endif

#if defined(__AT90Tiny2313__) | defined(__ATtiny2313__)
#define DDR_USI DDRB
#define PORT_USI PORTB
#define PIN_USI PINB
#define PORT_USI_SDA PORTB5
#define PORT_USI_SCL PORTB7
#define PIN_USI_SDA PINB5
#define PIN_USI_SCL PINB7
#define USI_START_COND_INT USISIF
#define TIMER_INT_MASK_REG TIMSK
#define OUTPUT_COMPARE_REG OCR0A
#define TIMER_CONTROL_REG TCCR0B
#define CLK_SELECT_PRESC_8 CS01
#define OUTPUT_COMP_INT_EN OCIE0A
#define USI_START_VECTOR USI_STRT_vect
#define USI_OVERFLOW_VECTOR USI_OVF_vect
#define TIMER_COMP_VECTOR TIMER0_COMPA_vect
#endif

#if defined(__ATtiny24__) | defined(__ATtiny44__) | defined(__ATtiny84__)
#define DDR_USI DDRA
#define PORT_USI PORTA
#define PIN_USI PINA
#define PORT_USI_SDA PORTA6
#define PORT_USI_SCL PORTA4
#define PIN_USI_SDA PINA6
#define PIN_USI_SCL PINA4
#define USI_START_COND_INT USISIF
#define USI_START_VECTOR USI_START_vect
#define USI_OVERFLOW_VECTOR USI_OVF_vect
#endif

#if defined(__ATtiny25__) | defined(__ATtiny45__) | defined(__ATtiny85__)
#define DDR_USI DDRB
#define PORT_USI PORTB
#define PIN_USI PINB
#define PORT_USI_SDA PORTB0
#define PORT_USI_SCL PORTB2
#define PIN_USI_SDA PINB0
#define PIN_USI_SCL PINB2
#define USI_START_COND_INT USICIF
#define TIMER_INT_MASK_REG TIMSK
#define OUTPUT_COMPARE_REG OCR0A
#define TIMER_CONTROL_REG TCCR0B
#define CLK_SELECT_PRESC_8 CS01
#define OUTPUT_COMP_INT_EN OCIE0A
#define USI_START_VECTOR USI_START_vect
#define USI_OVERFLOW_VECTOR USI_OVF_vect
#define TIMER_COMP_VECTOR TIM0_COMPA_vect
#endif

#if defined(__AT90Mega165__) | defined(__ATmega165__) | defined(__ATmega325__) | defined(__ATmega3250__)               \
    | defined(__ATmega645__) | defined(__ATmega6450__) | defined(__ATmega329__) | defined(__ATmega3290__)              \
    | defined(__ATmega649__) | defined(__ATmega6490__)
#define DDR_USI DDRE
#define PORT_USI PORTE
#define PIN_USI PINE
#define PORT_USI_SDA PORTE5
#define PORT_USI_SCL PORTE4
#define PIN_USI_SDA PINE5
#define PIN_USI_SCL PINE4
#define USI_START_COND_INT USISIF
#define TIMER_INT_MASK_REG TIMSK0
#define OUTPUT_COMPARE_REG OCR0A
#define TIMER_CONTROL_REG TCCR0A
#define CLK_SELECT_PRESC_8 CS01
#define OUTPUT_COMP_INT_EN OCIE0A
#define USI_START_VECTOR USI_START_vect
#define USI_OVERFLOW_VECTOR USI_OVERFLOW_vect
#define TIMER_COMP_VECTOR TIMER0_COMP_vect
#endif

#if defined(__AT90Mega169__) | defined(__ATmega169__) | defined(__AVR_ATmega169PA__)
#define DDR_USI DDRE
#define PORT_USI PORTE
#define PIN_USI PINE
#define PORT_USI_SDA PORTE5
#define PORT_USI_SCL PORTE4
#define PIN_USI_SDA PINE5
#define PIN_USI_SCL PINE4
#define USI_START_COND_INT USISIF
#define TIMER_INT_MASK_REG TIMSK0
#define OUTPUT_COMPARE_REG OCR0A
#define TIMER_CONTROL_REG TCCR0A
#define CLK_SELECT_PRESC_8 CS01
#define OUTPUT_COMP_INT_EN OCIE0A
#define USI_START_VECTOR USI_STRT_vect
#define USI_OVERFLOW_VECTOR USI_OVF_vect
#define TIMER_COMP_VECTOR TIMER0_COMP_vect
#endif

#define SET_USI_TO_SEND_ACK()                                                                                          \
	{                                                                                                                  \
		USIDR = 0;                      /* Prepare ACK                         */                                      \
		DDR_USI |= (1 << PORT_USI_SDA); /* Set SDA as output                   */                                      \
		USISR = (0 << USI_START_COND_INT) | (1 << USIOIF) | (1 << USIPF) | (1 << USIDC)                                \
		        |                  /* Clear all flags, except Start Cond  */                                           \
		        (0x0E << USICNT0); /* set USI counter to shift 1 bit. */                                               \
	}

#define SET_USI_TO_SEND_NACK()                                                                                          \
	{                                                                                                                  \
		DDR_USI &= ~(1 << PORT_USI_SDA); /* Set SDA as intput, NACK is SDA high */                                     \
		USISR = (0 << USI_START_COND_INT) | (1 << USIOIF) | (1 << USIPF) | (1 << USIDC)                                \
		        |                  /* Clear all flags, except Start Cond  */                                           \
		        (0x0E << USICNT0); /* set USI counter to shift 1 bit. */                                               \
	}

#define SET_USI_TO_READ_ACK()                                                                                          \
	{                                                                                                                  \
		DDR_USI &= ~(1 << PORT_USI_SDA); /* Set SDA as intput */                                                       \
		USIDR = 0;                       /* Prepare ACK        */                                                      \
		USISR = (0 << USI_START_COND_INT) | (1 << USIOIF) | (1 << USIPF) | (1 << USIDC)                                \
		        |                  /* Clear all flags, except Start Cond  */                                           \
		        (0x0E << USICNT0); /* set USI counter to shift 1 bit. */                                               \
	}

#define SET_USI_TO_TWI_START_CONDITION_MODE()                                                                          \
	{                                                                                                                  \
		DDR_USI &= ~(1 << PORT_USI_SDA); /* Set SDA as intput */                                                       \
		USICR = (1 << USISIE) | (0 << USIOIE) | /* Enable Start Condition Interrupt. Disable Overflow Interrupt.*/     \
		        (1 << USIWM1) | (0 << USIWM0) | /* Set USI in Two-wire mode. No USI Counter overflow hold.      */     \
		        (1 << USICS1) | (0 << USICS0) | (0 << USICLK)                                                          \
		        | /* Shift Register Clock Source = External, positive edge        */                                   \
		        (0 << USITC);                                                                                          \
		USISR = (0 << USI_START_COND_INT) | (1 << USIOIF) | (1 << USIPF) | (1 << USIDC)                                \
		        | /* Clear all flags, except Start Cond                            */                                  \
		        (0x0 << USICNT0);                                                                                      \
	}

#define SET_USI_TO_SEND_DATA()                                                                                         \
	{                                                                                                                  \
		DDR_USI |= (1 << PORT_USI_SDA); /* Set SDA as output                  */                                       \
		USISR = (0 << USI_START_COND_INT) | (1 << USIOIF) | (1 << USIPF) | (1 << USIDC)                                \
		        |                 /* Clear all flags, except Start Cond */                                             \
		        (0x0 << USICNT0); /* set USI to shift out 8 bits        */                                             \
	}

#define SET_USI_TO_READ_DATA()                                                                                         \
	{                                                                                                                  \
		DDR_USI &= ~(1 << PORT_USI_SDA); /* Set SDA as input                   */                                      \
		USISR = (0 << USI_START_COND_INT) | (1 << USIOIF) | (1 << USIPF) | (1 << USIDC)                                \
		        |                 /* Clear all flags, except Start Cond */                                             \
		        (0x0 << USICNT0); /* set USI to shift out 8 bits        */                                             \
	}

// Where is the LED connected?
// Port	: A
// Pin	: 5

#define PERIPH_BASE				(0x40000000UL)

#define APB2PERIPH_OFFSET		(0x00010000UL)
#define APB2PERIPH_BASE			(PERIPH_BASE + APB2PERIPH_OFFSET)

#define GPIOA_OFFSET			(0x0800UL)
#define GPIOA_BASE				(APB2PERIPH_BASE + GPIOA_OFFSET)

#define AHBPERIPH_OFFSET		(0x00018000)
#define AHBPERIPH_BASE			(PERIPH_BASE + AHBPERIPH_OFFSET)

#define RCC_OFFSET				(0x9000UL)
#define RCC_BASE				(AHBPERIPH_BASE + RCC_OFFSET)

#define RCC_APB2EN_R_OFFSET		(0x18UL)
#define RCC_APB2EN_R			(* (volatile unsigned int *)(RCC_BASE + RCC_APB2EN_R_OFFSET))

#define CRL_L_OFFSET			(0x00UL)
#define GPIOA_CRL_L				(* (volatile unsigned int *)(GPIOA_BASE + CRL_L_OFFSET))

#define OD_R_OFFSET				(0x0CUL)
#define GPIOA_OD_R				(* (volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define IOPAEN					(1U<<2) // 0b 0000 0000 0000 0000 0000 0000 0000 0100 # bit 2 of IO port A clock enable

#define PIN5					(1U<<5)
#define LED_PIN					PIN5


int main(void)
{
	/* 1. Enable clock access GPIOA */
	RCC_APB2EN_R |= IOPAEN; // OR the bits

	/* 2. Set PA5 as output mode */
	GPIOA_CRL_L |= (1U<<20); // Set bit 20 to 1
	GPIOA_CRL_L &=~ (1U<<21); // Set bit 21 to 0
	GPIOA_CRL_L &=~ (1U<<22); // Set bit 22 to 0
	GPIOA_CRL_L &=~ (1U<<23); // Set bit 23 to 0

	while(1)
	{
		/* 3. Set PA5 high. */
		// GPIOA_OD_R |= LED_PIN;

		/* 4. Experiment #2: toggle PA5 */
		GPIOA_OD_R ^= LED_PIN;
		for(int i = 0; i<100000; i++){}
	}

}

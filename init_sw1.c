void init_sw1(void)
{
	SYSCTL_RCGCGPIO_R |=0x20;
	while((SYSCTL_RCGCGPIO_R & 0x20) == 0);
	GPIO_PORTF_LOCK_R =0x4C4F434B;
	GPIO_PORTF_CR_R|=0x10;
	GPIO_PORTF_AMSEL_R&=~0x10;
	GPIO_PORTF_PCTL_R&=~0x000F0000;
	GPIO_PORTF_AFSEL_R&=~0x10;
	GPIO_PORTF_DIR_R &=~ 0x10;
	GPIO_PORTF_PUR_R|=0x10;
	GPIO_PORTF_DEN_R|=0x10;
}
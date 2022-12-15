#include "ece353.h"
#include "msp.h"
//****************************************************
//****************************************************
// 02-Ex-Code-Organization
//****************************************************
//****************************************************

/* ***************************************************
 * Initialize hardware resources used to control LED1
 *****************************************************/
void ece353_led1_init(void)
{
    //set direction
    P1->DIR |=BIT0;
    //turn off
    P1->OUT &= ~BIT0;
}

/*****************************************************
 * Initialize hardware resources used to control Button1
 *****************************************************/
void ece353_button1_init(void)
{
    //set to input
    P1->DIR &= ~BIT1;
    //enable resistor
    P1->REN |=BIT1;
    //select pull up
    P1->OUT |= BIT1;
}

/*****************************************************
 * Turn LED1 ON/Off.
 *
 * Parameters
 *  on: if true,  turn LED on
 *      if false, turn LED off
 *****************************************************/
void ece353_led1(bool on)
{//true is on
    if (on){
    //turn led on
    P1->OUT |=BIT0;
     }
    else{
    P1->OUT &= ~BIT0;
    }


}

/*****************************************************
 * Returns if Button1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button1 is pressed
 *      false   :   Button1 is NOT pressed
 *****************************************************/
bool ece353_button1(void)
{
    if ((P1->IN & BIT1) == 0){
        return true;
    }
    else{
    return false;
    }

}



//****************************************************
//****************************************************
// 02-ICE-Code-Organization
//****************************************************
//****************************************************

/*****************************************************
 * Initialize hardware resources used to control RGBLED
 *****************************************************/
void ece353_rgb_init(void)
{   //red
//set direction
    P2->DIR |=BIT0;
//turn off
    P2->OUT &= ~BIT0;

  //green
//set direction
    P2->DIR |=BIT1;
//turn off
    P2->OUT &= ~BIT1;

    //blue
//set direction
    P2->DIR |=BIT2;
//turn off
    P2->OUT &= ~BIT2;
}

/*****************************************************
 * Turn RGBLED ON/Off.
 *
 * Parameters
 *  red_on      :   if true,  turn RGBLED.RED on
 *                  if false, turn RGBLED.RED off
 *  green_on    :   if true,  turn RGBLED.GREEN on
 *                  if false, turn RGBLED.GREEN off
 *  blue_on     :   if true,  turn RGBLED.BLUE on
 *                  if false, turn RGBLED.BLUE off
 *****************************************************/
void ece353_rgb(bool red_on, bool green_on, bool blue_on)
{
    if (red_on)//red
    {
        P2->OUT |= BIT0;//red on
    }
    else{//red off
        P2->OUT &= ~BIT0;
    }

    if (green_on)//green
    {
        P2->OUT |= BIT1;
    }
    else{//green off
        P2->OUT &= ~BIT1;
    }

    if (blue_on)//blue
    {
        P2->OUT |= BIT2;
    }
    else{//blue off
        P2->OUT &= ~BIT2;
    }

}

/*****************************************************
 * Initialize hardware resources used to control Button2
 *****************************************************/
void ece353_button2_init(void)
{
    //set to input
    P1->DIR &= ~BIT4;
//enable resistor
    P1->REN |=BIT4;
//select pull up
    P1->OUT |= BIT4;
}

/*****************************************************
 * Returns if Button2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button2 is pressed
 *      false   :   Button2 is NOT pressed
 *****************************************************/
bool ece353_button2(void)
{
    if ((P1->IN & BIT4) == 0){
        return true;
    }
    else{
    return false;
    }
}

//*****************************************************************************
//*****************************************************************************
// ICE 03 - Timer32_1 Push Button Detection
//*****************************************************************************
//*****************************************************************************

/*****************************************************
 * Busy waits for 100mS and then returns.
 *
 * Timer32_1 MUST be configured as a 16-bit timer.
 * Assume that the MCU clock runs at 3MHz.  You will
 * need to use a pre-scalar in order to achieve a delay
 * of 100mS.
 *
 * Parameters:
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_T32_1_wait_100mS(void){
    int ticks = 3000000/16*0.1;

    //stop timer
    TIMER32_1->CONTROL =0; //all off

        //set timer to 32 bit one shot
    TIMER32_1->CONTROL = TIMER32_CONTROL_ONESHOT |TIMER32_CONTROL_SIZE | BIT2 & ~BIT3;
        //set the load int
    TIMER32_1->LOAD = ticks;

        //start the timer
    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE; //or so that we don't lose info

        //wait till reaches 0
    while(TIMER32_1->VALUE!=0){
            //wait till ends
     }
}


/*****************************************************
 * Debounces Button1 using Timer32_1.
 * This function does not return until Button 1 has
 * been pressed for a minimum of 5 seconds.
 *
 * Waiting 5 Seconds will require you to call
 * ece353_T32_1_wait_100mS multiple times.
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_button1_wait_for_press(void){
    int n=0;//how many waits do we need to do
    while (n!=50){
       ece353_T32_1_wait_100mS();
       n+=1;
       if (!ece353_button1()){
           n=0;
       }
    }


}




//*****************************************************************************
//*****************************************************************************
// ICE 04 - PWMing MKII tri-color LED.
//*****************************************************************************
//*****************************************************************************

/*****************************************************
 * Initialize the 3 GPIO pins that control the RGB
 * LED on the MKII.
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_IO_Init(bool en_primary_function)
{

    // Complete the comments below to identify which pins
    // control which LEDs.
    //
    // Replace a and c with the correct port number
    // Replace b and d with the correct pin numbers.
    // RED      : P2.6 to j4.39
    // GREEN    : P2.4 to  j4.38
    // BLUE     : P5.6 to j4.37

    // ADD CODE that configures the RED, GREEN, and
    // BLUE LEDs to be outputs

    //red
    //set direction
        P2->DIR |=BIT6;
    //turn off
        P2->OUT &= ~BIT6;

      //green
    //set direction
        P2->DIR |=BIT4;
    //turn off
        P2->OUT &= ~BIT4;

        //blue
    //set direction
        P5->DIR |=BIT6;
    //turn off
        P5->OUT &= ~BIT6;


    // ADD CODE that selects the Primary module function
    // for all 3 pins
    if(en_primary_function)
    {
        //Set timer pwm controller
        P2->SEL0 |=  BIT6;
        P2->SEL1 &= ~BIT6;
        //Set timer pwm controller
        P2->SEL0 |=  BIT4;
        P2->SEL1 &= ~BIT4;
        //Set timer pwm controller
        P5->SEL0 |=  BIT6;
        P5->SEL1 &= ~BIT6;

    }

}

/*****************************************************
 * Sets the PWM levels for the MKII RGBLED
 *
 * Parameters
 *      ticks_period    :   Period of PWM Pulse
 *      red_num         :   RED RGB Number
 *      green_num       :   GREEN RGB Number
 *      blue_num        :   BLUE RGB Number
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_PWM(
        uint16_t ticks_period,
        uint16_t red_num,
        uint16_t green_num,
        uint16_t blue_num
)
{
    // This code converts the HTML color codes into a 
    // number of clock ticks used to generate the duty cyle of
    // the PWM signal.
    uint16_t ticks_red_on = (red_num * ticks_period)/255;
    uint16_t ticks_green_on = (green_num * ticks_period)/255;
    uint16_t ticks_blue_on = (blue_num * ticks_period)/255;

    // Initialze the IO pins used to control the
    // tri-color LED.
    ece353_MKII_RGB_IO_Init(true);

    // Complete the comments below that identify which
    // TimerA outputs will control the IO pins.
    //
    // Replace w and y with the correct TimerA number
    // Replace x and z with the correct CCR number.
    // RED      <--> TA0.3
    // GREEN    <--> TA0.1
    // BLUE     <--> TA2.1

    // ADD CODE BELOW setting them to reset/set

    // Turn off the timer peripherals
    TIMER_A0->CTL = 0;
    TIMER_A2->CTL = 0;
    // Set the period for both TimerA peripherals.
    TIMER_A0->CCR[0] = ticks_period-1;
    TIMER_A2->CCR[0] = ticks_period-1;
    // Configure RED PWM duty cycle
    TIMER_A0 -> CCR[3]=ticks_red_on;
    // Configure GREEN PWM duty cycle
    TIMER_A0 -> CCR[1]=ticks_green_on;
    // Configure BLUE PWM duty cycle
    TIMER_A2 -> CCR[1]=ticks_blue_on;
    // Set the OUT MODE to be mode 7 for each
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A2->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;

    // Turn the first TimerA peripheral on.  Be sure to use SMCLK as the clock source
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK|TIMER_A_CTL_MC__UP;
    // Turn the second TimerA peripheral on.  Be sure to use SMCLK as the clock source
    TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK|TIMER_A_CTL_MC__UP;
}
//Initialize hardware resources used to control S1
void ece353_MKII_S1_Init(void){
    //config as input
        P5->DIR &= ~BIT1;
       //has internal pullups so no need
}
//Initialize hardware resources used to control S2
void ece353_MKII_S2_Init(void){
    //config as input
        P3->DIR &= ~BIT5;
       //has internal pullups so no need
}

/*****************************************************
 * returns if mkil.s1 is correctly pressed
 *
 * Parameters
 *  on: if true,  button1 is pressed
 *      if false, button1 is not pressed
 *****************************************************/
bool ece353_MKII_S1(void){
    return !((P5->IN)& BIT1);
}
/*****************************************************
 * returns if mkil.s2 is correctly pressed
 *
 * Parameters
 *  on: if true,  button2 is pressed
 *      if false, button2 is not pressed
 *****************************************************/
bool ece353_MKII_S2(void){
    return !((P3->IN)& BIT5);
}
void ece353_MKII_Buzzer_Init(uint16_t ticks_period){
    //configure gpio pin
    //output
    P2->DIR |=BIT7;
    //Set timer pwm controller
    P2->SEL0 |=  BIT7;
    P2->SEL1 &= ~BIT7;
    //configure the timer, what clock, and clock mode
    //turn off TA0
    TIMER_A0->CTL = 0;
    //0 ALWAYS SETS THE PERIOD
    TIMER_A0->CCR[0] = ticks_period-1;
    //DUTY IS 50%
    TIMER_A0 -> CCR[4]=(ticks_period/2)-1;
    //CONFIG TA0.4 FOR RESET/SET MODE
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;
    //SELECT MASTER CLOCK AS THE TIMER SOURCE
    //TIMER_A0->CTL = TIMER_A_CTL_SMCLK;
}

/*****************************************************
 *turns buzzer on
 *****************************************************/
void ece353_MKII_Buzzer_On(void){
    //CLEAR THE CURRENT MODE CONTROL BITS
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;
    //SET MODE CONTROL TO UP AND CLEAR THE CURRENT
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP| TIMER_A_CTL_CLR;
}


/*****************************************************
 *turns buzzer off
 *****************************************************/
void ece353_MKII_Buzzer_Off(void){
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;
}


/*****************************************************
 *Check buzzer run status
 *Parameters
 *       None
 * Returns
 *      True if timerA0 is On.
 *      False if timerA0 is Off.
 *****************************************************/
bool ece353_MKII_Buzzer_Run_Status(void){
    return !(TIMER_A0->CTL&TIMER_A_CTL_MC_MASK);
}
void ice05_init_s1(void)
{
    // Configure the pin connected to S1 as an input
    ece353_MKII_S1_Init();
    // Set the interrupt event to be a High to Low transition
    // IES Regiter (Interrupt Edge Select)
    P5->IES |= BIT1;

    // Enable interrupts in the peripheral
    P5->IE |= BIT1;
    //TIMER32_1->CONTROL = TIMER32_CONTROL_ENABLE | TIMER32_CONTROL_MODE|TIMER32_CONTROL_SIZE|TIMER32_CONTROL_IE; //TIMER ON, PERIODIC,32 BIT TIMER, ENABLE INTERRUPT(PERIPHERALLY)

    // Enable the NVIC
   // __enable_irq();

    // Enable the IO Port interrupts in the NVIC
    NVIC_EnableIRQ(PORT5_IRQn);//NUMS DFINED IN A GIVEN FILE LIB

    // Set the priority of the IO Port interrupt to 0
    NVIC_SetPriority(PORT5_IRQn,0);

}
//all numbers of interrupts are in msp432p401r.h and msp432p401r_ccs.h
volatile bool ALERT_S1_PRESSED = false;  ///global
void PORT5_IRQHandler(void)
{
    // Variables needed for ISR
    // Do NOT add additional variables
    static int irq_count = 0;
    uint32_t reg_val;

    // increment the count.
    irq_count = irq_count +1;

    //If the count is > 10, alert the main application
    if (irq_count > 10){ //finish bouncing
                ALERT_S1_PRESSED = true; //aka not bouncing anymore
    }
    // Clear the interrupt.  Be sure to read the section of the
    // MSP432 TRM related to IO Interrupts to determine how to clear
    // an interrupt.
    reg_val = P5->IV;

}


//*****************************************************************************
//*****************************************************************************
// ICE 06 - ADC14
//*****************************************************************************
/******************************************************************************
 * Configure the IO pins for BOTH the X and Y directions of the analog
 * joystick.  The X direction should be configured to place the results in
 * MEM[0].  The Y direction should be configured to place the results in MEM[1].
 *
 * After BOTH analog signals have finished being converted, a SINGLE interrupt
 * should be generated.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
extern volatile uint32_t PS2_X_DIR = 0;
extern volatile uint32_t PS2_Y_DIR = 0;

void ece353_ADC14_PS2_XY(void)
{
    // Configure the X direction as an analog input pin.
    P6->SEL0 |=BIT0; //input to the pin x is connected
    P6->SEL1 |=BIT0;

    // Configure the Y direction as an analog input pin.
    P4->SEL0 |=BIT4; //input to the pin y is connected
    P4->SEL1 |=BIT4;

    // Configure CTL0 to sample 16-times in pulsed sample mode.
    // NEW -- Indicate that this is a sequence-of-channels.
    ADC14->CTL0 = ADC14_CTL0_SHP| ADC14_CTL0_SHT02|ADC14_CTL0_MSC|ADC14_CTL0_CONSEQ_1;

    // Configure ADC to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_2;

    // Associate the X direction analog signal with MEM[0]
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_15; // FOR A15 for x mem

    // Associate the Y direction analog signal with MEM[1]
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_9; // FOR A0 for y mem

    // NEW -- Make sure to indicate this is the end of a sequence.
    //ADC14->MCTL[0]|= ADC14_MCTLN_EOS;
    ADC14->MCTL[1]|= ADC14_MCTLN_EOS;

    // Enable interrupts in the ADC AFTER a value is written into MEM[1].
    ADC14->IER0 = ADC14_IER0_IE1;
//
// NEW: This is not the same as what is demonstrated in the example
// coding video.
    // Enable ADC Interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);
    // Turn ADC ON
    ADC14->CTL0|= ADC14_CTL0_ON;

}
/*****************************************************
 * Turn RGB on the MKII LED ON/Off.
 *
 * Parameters
 *  red:    if true,  turn RED LED on
 *          if false, turn RED LED off
 *  green:  if true,  turn GREEN LED on
 *          if false, turn GREEN LED off
 *  blue:   if true,  turn BLUE LED on
 *          if false, turn BLUE LED off
 *****************************************************/
void ece353_MKII_RGB_LED(bool red, bool green, bool blue)
{
   //blue is j4.37
    //green is j4.38
    //red is j4.39
    // RED      : P2.6 to j4.39
    // GREEN    : P2.4 to  j4.38
    // BLUE     : P5.6 to j4.37

    if (red)//red
    {
        P2->OUT |= BIT6;//red on
    }
    else{//red off
        P2->OUT &= ~BIT6;
    }

    if (green)//green
    {
        P2->OUT |= BIT4;
    }
    else{//green off
        P2->OUT &= ~BIT4;
    }

    if (blue)//blue
    {
        P5->OUT |= BIT6;
    }
    else{//blue off
        P5->OUT &= ~BIT6;
    }
}
#define VOLT_0P85 1056  // 1056      // 0.85 /(3.3/4096)
#define VOLT_2P50 3103 // 3103      // 2.50 /(3.3/4096)



void ece353_ADC14_PS2_X_COMP(void)
{
    // Configure the X direction as an analog input pin.
    P6->SEL0 |=BIT0; //input to the pin x is connected
    P6->SEL1 |=BIT0;



    // Configure CTL0 to sample 16-times in pulsed sample mode.
    //ADC14->CTL0 = ADC14_CTL0_SHP| ADC14_CTL0_SHT02|ADC14_CTL0_MSC;//|ADC14_CTL0_CONSEQ_1
    ADC14->CTL0 = ADC14_CTL0_SHP| ADC14_CTL0_SHT02;

    // Configure CTL1 to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_2;

    // Set up the HI0 Window
    ADC14->HI0 = VOLT_2P50;

    // Set up the LO0 Window
    ADC14->LO0 = VOLT_0P85;

    // Associate the X direction analog signal with MEM[0], indicate the end of sequence,
// turn on the window comparator
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_15; // FOR A15 for x mem

    // Enable interrupts when either the HI or LO thresholds of the window
    // comparator has been exceeded.  Disable all other interrupts
    //ADC14->IER0 = ADC14_IER0_IE1;
    //ADC14->MCTL[0] &= ~BIT15;
    ADC14->IER0 = ADC14_IER0_IE0;
    ADC14->IER1 |= ADC14_IER1_HIIE|ADC14_IER1_LOIE|ADC14_IER1_INIE;

    // Enable ADC Interrupt
    NVIC_EnableIRQ(ADC14_IRQn);
    // Turn ADC ON
    ADC14->CTL0|= ADC14_CTL0_ON;
}

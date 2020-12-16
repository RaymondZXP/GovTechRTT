#include <stdint.h>
#include <stdbool.h>
#include "product.h"
#include "timer.h"

void timer0_init(void)
{
    /* Initialise the timer 0*/
    NRF_TIMER0->MODE = TIMER_MODE_MODE_Timer;
    NRF_TIMER0->BITMODE = (TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos);
    NRF_TIMER0->TASKS_STOP = 1;
    NRF_TIMER0->EVENTS_COMPARE[0] = 0;
    NRF_TIMER0->EVENTS_COMPARE[1] = 0;
    NRF_TIMER0->EVENTS_COMPARE[2] = 0;
    NRF_TIMER0->EVENTS_COMPARE[3] = 0;
    NRF_TIMER0->SHORTS = (TIMER_SHORTS_COMPARE3_CLEAR_Enabled << TIMER_SHORTS_COMPARE3_CLEAR_Pos) |
                         (TIMER_SHORTS_COMPARE3_STOP_Enabled << TIMER_SHORTS_COMPARE3_STOP_Pos);
    NRF_TIMER0->PRESCALER = 4 << TIMER_PRESCALER_PRESCALER_Pos; /* input clock is 16MHz, timer clock = 2 ^ prescale */
    NRF_TIMER0->TASKS_CLEAR = 1;
}

void timer0_start(uint32_t timeout_us)
{
    NRF_TIMER0->TASKS_STOP = 1;
    NRF_TIMER0->CC[3] = timeout_us;
    NRF_TIMER0->TASKS_CLEAR = 1;
    NRF_TIMER0->EVENTS_COMPARE[3] = 0;
    NRF_TIMER0->TASKS_START = 1;
}

bool timer0_timeout(void)
{
    if (NRF_TIMER0->EVENTS_COMPARE[3] != 0)
    {
        return true;
    }
    return false;
}

void timer0_capture_init(uint32_t prescaler)
{
    NRF_TIMER0->MODE = TIMER_MODE_MODE_Timer;
    NRF_TIMER0->BITMODE = (TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos);
    NRF_TIMER0->TASKS_STOP = 1;
    NRF_TIMER0->CC[0] = 0x0000;
    NRF_TIMER0->EVENTS_COMPARE[0] = 0;
    NRF_TIMER0->EVENTS_COMPARE[1] = 0;
    NRF_TIMER0->EVENTS_COMPARE[2] = 0;
    NRF_TIMER0->EVENTS_COMPARE[3] = 0;
    NRF_TIMER0->TASKS_CLEAR = 1;
    NRF_TIMER0->SHORTS = 0;
    NRF_TIMER0->PRESCALER = prescaler << TIMER_PRESCALER_PRESCALER_Pos;
    NRF_TIMER0->TASKS_CLEAR = 1;
}

void timer0_capture_start(void)
{
    NRF_TIMER0->TASKS_START = 1;
}

uint32_t timer0_capture_now(void)
{
    uint32_t capture;
    NRF_TIMER0->TASKS_CAPTURE[0] = 1;
    NRF_TIMER0->TASKS_STOP = 1;
    capture = NRF_TIMER0->CC[0];
    NRF_TIMER0->TASKS_CLEAR = 1;
    return capture;
}

void timer1_init(void)
{
    /* Initialise the timer 0*/
    NRF_TIMER1->MODE = TIMER_MODE_MODE_Timer;
    NRF_TIMER1->BITMODE = (TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos);
    NRF_TIMER1->TASKS_STOP = 1;
    NRF_TIMER1->EVENTS_COMPARE[0] = 0;
    NRF_TIMER1->EVENTS_COMPARE[1] = 0;
    NRF_TIMER1->EVENTS_COMPARE[2] = 0;
    NRF_TIMER1->EVENTS_COMPARE[3] = 0;
    NRF_TIMER1->SHORTS = (TIMER_SHORTS_COMPARE3_CLEAR_Enabled << TIMER_SHORTS_COMPARE3_CLEAR_Pos) |
                         (TIMER_SHORTS_COMPARE3_STOP_Enabled << TIMER_SHORTS_COMPARE3_STOP_Pos);
    NRF_TIMER1->PRESCALER = 4 << TIMER_PRESCALER_PRESCALER_Pos; /* input clock is 16MHz, timer clock = 2 ^ prescale */
    NRF_TIMER1->TASKS_CLEAR = 1;
}

void timer1_start(uint32_t timeout_us)
{
    NRF_TIMER1->TASKS_STOP = 1;
    NRF_TIMER1->CC[3] = timeout_us;
    NRF_TIMER1->TASKS_CLEAR = 1;
    NRF_TIMER1->EVENTS_COMPARE[3] = 0;
    NRF_TIMER1->TASKS_START = 1;
}

bool timer1_timeout(void)
{
    if (NRF_TIMER1->EVENTS_COMPARE[3] != 0)
    {
        return true;
    }
    return false;
}

void timer1_capture_init(uint32_t prescaler)
{
    NRF_TIMER1->MODE = TIMER_MODE_MODE_Timer;          // Set the timer in Counter Mode
    NRF_TIMER1->TASKS_CLEAR = 1;                       // clear the task first to be usable for later
    NRF_TIMER1->PRESCALER = prescaler;                         //Set prescaler. Higher number gives slower timer. Prescaler = 0 gives 16MHz timer
    NRF_TIMER1->BITMODE = TIMER_BITMODE_BITMODE_16Bit; //Set counter to 16 bit resolution
    NRF_TIMER1->CC[0] = 1000;                         //Set value for TIMER1 compare register 0
    // NRF_TIMER1->CC[1] = 5;                                 //Set value for TIMER2 compare register 1

    // Enable interrupt on Timer 1 for CC[0] compare match events
    NRF_TIMER1->INTENSET = (TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos);
    NVIC_EnableIRQ(TIMER1_IRQn);

    NRF_TIMER1->TASKS_START = 1; // Start TIMER1
}


uint32_t timer1_capture_now(void)
{
    uint32_t capture;
    NRF_TIMER1->TASKS_CAPTURE[0] = 1;
    NRF_TIMER1->TASKS_STOP = 1;
    capture = NRF_TIMER1->CC[0];
    NRF_TIMER1->TASKS_CLEAR = 1;
    return capture;
}

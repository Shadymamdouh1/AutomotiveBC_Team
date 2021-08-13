/*
 * ISR_Cfg.h
 *
 * Created: 8/12/2021 10:58:09 PM
 *  Author: 
 */ 


#ifndef ISR_CFG_H_
#define ISR_CFG_H_

#define LOW_LEVEL			0			//The low level of INT0 generates an interrupt request.
#define LOGIC_CHANGE		1			//Any logical change on INT0 generates an interrupt request.
#define FALLING_EDGE		2			//The falling edge of INT0 generates an interrupt request.
#define RISING_EDGE			3			//The rising edge of INT0 generates an interrupt request.




#endif /* ISR_CFG_H_ */
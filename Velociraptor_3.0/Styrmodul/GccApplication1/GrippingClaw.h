/*
 * GrippingClaw.h
 *
 * Created: 12/5/2015 12:52:35 PM
 *  Author: marlu642
 */ 


#ifndef GRIPPINGCLAW_H_
#define GRIPPINGCLAW_H_

// Make the gripping claw move towards claw_position.
// Good values are somewhere between 250-400. 
// At 250 the claw is closed shut and at 400 the claw is wide open aka claw position.
void grab_object(int claw_position);
// Initializes the gripping claw
void init_gripping_claw_timer();

#endif /* GRIPPINGCLAW_H_ */

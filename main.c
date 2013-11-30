#include <msp430.h>

int main(void)
{
	InitRobot ();

    while (1) {
    	MoveRobotForward ();

    	MoveRobotBackwards ();

    	MoveRobotLeftS ();

    	MoveRobotRightS ();

    	MoveRobotLeftL ();

    	MoveRobotRightL ();
    }

    return 0;
}

#ifndef DROPOFFCONTROLLER_H
#define DROPOFFCONTROLLER_H
#define HEADERFILE_H

#include <geometry_msgs/Pose2D.h>
#include <std_msgs/Float32.h>
#include <ros/ros.h>


class DropOffController
{
public:
    DropOffController();
    ~DropOffController();

int state;
const static int FINDING_BASE = 0, ADJUSTING_ANGLE_FOR_ENTRY = 1, ENTERING_BASE = 2, DROPPING_CUBE = 3, BACKING_OUT_OF_BASE = 4, DONE_DROPPING_OFF = 5,
	 PAUSING_BEFORE_ROTATING_AGAIN = 6, SCOOTING_CLOSER_TO_BASE = 7;
    
    void setDataTargets(int numLeft, int numRight);
int getState(){return state;}
	void setState(int stateSet){state = stateSet;}
void reset();
void setTagCountToZeroIfAppropriate();
int getCountLeft(){return countLeft;}
int getCountRight(){return countRight;}

ros::Time omniTimerStartingTime;
ros::Time lastTimeISawTheCenterBase;

std::string getStateName() {
const std::string stateNames[] = {"FINDING_BASE","ADJUSTING_ANGLE_FOR_ENTRY","ENTERING_BASE","DROPPING_CUBE","BACKING_OUT_OF_BASE","DONE_DROPPING_OFF"
		,"PAUSING_BEFORE_ROTATING_AGAIN","SCOOTING_CLOSER_TO_BASE"};
return stateNames[getState()];
}

const static float FINGERS_OPEN = M_PI_2;
const static float FINGERS_CLOSED = 0;
const static float WRIST_UP = 0;
const static float WRIST_DOWN = 1.25;

/*
these two variables, numTimesPausedAndTurned & giveUpAndDropAfterTurningThisManyTimes are for when the robot is stuck between ADJUSTING_ANGLE_FOR_ENTRY and PAUSING_BEFORE_ROTATING_AGAIN because he is parallel with one of the edges of the collection point.
*/
int numTimesPausedAndTurned;//this is a "give up" variable
const static int giveUpAndDropAfterTurningThisManyTimes = 8;

private:
    int countLeft;
    int countRight;
};
#endif // end header define

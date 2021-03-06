#ifndef PICKUPCONTROLLER_H
#define PICKUPCONTROLLER_H
#define HEADERFILE_H
#include <apriltags_ros/AprilTagDetectionArray.h>
#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include "Calibration.h"

struct PickUpResult {
  float cmdVel;
  float angleError;
  volatile float fingerAngle;
  volatile float wristAngle;
  bool pickedUp;
float blockDist;
float blockYawError;
float debug;
bool foundACluster;
};

class PickUpController
{
 public:
  bool blockBlock;
  PickUpController();
  ~PickUpController();
const static float PICKUP_VELOCITY = 0.10;

  PickUpResult selectTarget(const apriltags_ros::AprilTagDetectionArray::ConstPtr& message);
  PickUpResult pickUpSelectedTarget(geometry_msgs::Pose2D currentLocation, Calibration);

  float getDist() {return blockDist;}
  bool getLockTarget() {return lockTarget;}
  float getTD() {return td;}//									the gripper length is 13 centimeters
void setDistanceToBlockUponFirstSight(float pls,float ok) {distanceToBlockUponFirstSight = pls - 0.00; yawErrorToBlockUponFirstSight = ok;}

int getState() {return state;}
void setState(int s){state = s;}

//for PID
bool checkedOnce;

  void reset();
const static int FIXING_CAMERA=0, APPROACHING_CUBE=1, PICKING_UP_CUBE=2,VERIFYING_PICKUP=3,PICKUP_FAILED_BACK_UP=4,DONE_FAILING=5,
		DONE_SUCCESS=6,WAIT_BEFORE_RAISING_WRIST=7,WAITING_AND_CHECKING_CAMERA_AGAIN=8;
volatile int state;

std::string getStateName() {
const std::string stateNames[] = {"FIXING_CAMERA", "APPROACHING_CUBE", "PICKING_UP_CUBE","VERIFYING_PICKUP", "PICKUP_FAILED_BACK_UP","DONE_FAILING",
		"DONE_SUCCESS","WAIT_BEFORE_RAISING_WRIST","WAITING_AND_CHECKING_CAMERA_AGAIN"};
return stateNames[getState()];
}


const static float FINGERS_OPEN = M_PI_2;
const static float FINGERS_CLOSED = 0;
const static float WRIST_UP = 0;
const static float WRIST_DOWN = 1.00;
const static float WRIST_CARRY = 0.80;

//this is set when you first switch to "state_pickup"
float distanceToBlockUponFirstSight;
float yawErrorToBlockUponFirstSight;
//yeah
float correctAngleBearingToPickUpCube;


//ok wheels please
float lastCmdVel;
float lastAngleError;


ros::Time omniTimerStartingTime;

private:
  //set true when the target block is less than targetDist so we continue attempting to pick it up rather than
  //switching to another block that is in view
  bool lockTarget; 
bool openCVThinksCubeIsHeld;

  // Failsafe state. No legitimate behavior state. If in this state for too long return to searching as default behavior.
  bool timeOut;
  bool thereIsAReallyCloseBlock;
  int nTargetsSeen;
  ros::Time millTimer;

  //yaw error to target block 
  double blockYawError;
  
  //distance to target block from front of robot
  double blockDist;

  //struct for returning data to mobility
  PickUpResult result;

  float td;
};
#endif // end header define

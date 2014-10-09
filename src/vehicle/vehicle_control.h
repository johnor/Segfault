#ifndef VEHICLE_DRIVE_CONTROL_H_
#define VEHICLE_DRIVE_CONTROL_H_

#define VEHICLE_MAX_SPEED_MAGNITUDE 100
#define VEHICLE_MAX_TURN_RATE_MAGNITUDE 100

void setVehicleSpeed(int signedSpeed);
void setVehicleTurnRate(int signedTurnRate);

#endif  /* VEHICLE_DRIVE_CONTROL_H_ */

#include "vex.h"

// Create a VEX object
using namespace vex;

// Initialize the brain
brain Brain;

// Initialize the controller
controller Controller;

// Initialize motor at port 1 with a gear ratio of 6:1
motor Motor1 = motor(PORT16, ratio6_1, false);



// Initialize pneumatic at analog port 1
digital_out Pneumatic1 = digital_out(Brain.ThreeWirePort.A);

// Function to control the motor and pneumatic based on controller input
void controlDevices() {
    while (true) {
        Motor1.setVelocity(350, rpm);
        // Control pneumatic with L2 and L1
        
        static bool pneumaticState = false;
        if (Controller.ButtonL2.pressing()) {
            if (pneumaticState){
            Pneumatic1.set(false); // Push in
            wait(100, msec);
            pneumaticState = false;
        } else if(!pneumaticState){
            Pneumatic1.set(true);
            wait(100, msec);
            pneumaticState = true;
        }
    static bool motorState = false; // Keeps track of the motor state
    if (Controller.ButtonR2.pressing()) {
    // Check the state of the motor and toggle
        if (motorState) {
            Motor1.stop(coast); // Stop the motor and apply brake
            motorState = false;  // Update state
        } else {
            Motor1.spin(forward); // Turn the motor on
            motorState = true;     // Update state
        }
    wait (200, msec);
        }

        // Control motor with R2 and R1
        if (Controller.ButtonA.pressing()) {
            Motor1.spin(reverse); // Spin motor backward
            wait(0.4, seconds); // Wait for 0.8 seconds
            if(motorState){
                Motor1.spin(forward);
            }else{
                Motor1.stop(coast);
        }}

        wait (20, msec);  // Small wait to prevent CPU overload
}}

int main() {
    // Start controlling devices
    controlDevices();

    // The controlDevices function will run indefinitely
    return 0;
}

//repo testing
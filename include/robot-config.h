using namespace vex;

extern brain Brain;
extern controller main_Controller;
extern motor LFDrive;
extern motor LBDrive;
extern motor RBDrive;
extern motor RFDrive;

extern motor l_horizontal_intake;
extern motor r_horizontal_intake;

extern motor u_vertical_intake;
extern motor l_vertical_intake;

extern rotation lEncoder;
extern rotation rEncoder;

// VEXcode devices

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
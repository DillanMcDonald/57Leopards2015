#include <Commands/LiftTopGroup.h>

LiftTopGroup::LiftTopGroup()
{
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.


//	AddParallel(new Open_Clamps());		//Placeholder for opening tote clamps
	AddSequential(new Open_Intake());  //Open Intake Arms
	AddSequential(new WaitCommand(0.100));  //Wait 0.100 sec for arms to start moving (might need longer here)
	AddSequential(new LiftTop(), 3.0);  //Send lift to top.  Timeout after 3 sec incase jam
//	AddParallel(new Close_Clamps());	//Placeholder for closing tote clamps
	AddSequential(new Close_Intake());  //Close Intake Arms


	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}

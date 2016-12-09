#ifndef EVOLVE_COMMAND
#define EVOLVE_COMMAND
class EvolveCommand: public AbstractCommand {
public:
	void execute();
	void undo();
};
#endif
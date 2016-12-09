#ifndef ABSTRACT_COMMAND
#define ABSTRACT_COMMAND
class AbstractCommand {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
}
#endif
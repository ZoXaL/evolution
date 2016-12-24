#ifndef ABSTRACT_CONTROLLER_H
#define ABSTRACT_CONTROLLER_H

class AbstractController {
public:
	virtual AbstractController* run() = 0;
};

#endif
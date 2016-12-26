#ifndef Prototype_H
#define Prototype_H

template<typename T>
class Prototype {
public:
	virtual T clone() = 0;
	virtual ~Prototype() {};
};
#endif
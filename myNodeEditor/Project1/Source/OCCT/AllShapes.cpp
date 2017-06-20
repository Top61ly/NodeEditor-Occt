#include "AllShapes.h"

AllShapes::AllShapes(){}
AllShapes::~AllShapes(){}

void AllShapes::addShape(TopoDS_Shape shape) {
	instance()._shapes.push_back(shape);
}

void AllShapes::clearShapes() {
	instance()._shapes.clear();
}

int AllShapes::size() {
	return instance()._shapes.size();
}

TopoDS_Shape const& AllShapes::getShape(int i) {
	return instance()._shapes[i];
}


AllShapes& AllShapes::instance() {
	static AllShapes instance;
	return instance;
}


#pragma once
#include <vector>

#include <TopoDS_Shape.hxx>

class AllShapes
{
	
public:
	AllShapes();
	~AllShapes();

	static void addShape(TopoDS_Shape shape);

	static void clearShapes();

	static int size();

	static TopoDS_Shape const& getShape(int i);

	static AllShapes& instance();

private:
	std::vector<TopoDS_Shape> _shapes;
};
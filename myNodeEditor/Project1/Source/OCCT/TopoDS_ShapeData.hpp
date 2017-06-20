#pragma once

#include <nodes/NodeDataModel>
#include <TopoDS_Shape.hxx>


using QtNodes::NodeDataType;
using QtNodes::NodeData;
/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class TopoDS_ShapeData : public NodeData
{
public:

	TopoDS_ShapeData()
	{}

	TopoDS_ShapeData(TopoDS_Shape shape)
	{
		_shape = shape;	
	}

	NodeDataType type() const override
	{
		return NodeDataType{ "shape",
			"Shape" };
	}

	TopoDS_Shape shape() const
	{
		return _shape;
	}

private:

	TopoDS_Shape _shape;
};

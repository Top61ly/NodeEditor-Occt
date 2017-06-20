#pragma once

#include <nodes/NodeDataModel>

#include "gp_Pnt.hxx"

using QtNodes::NodeDataType;
using QtNodes::NodeData;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class gp_PntData : public NodeData
{
public:

	gp_PntData()
		: _point()
	{}

	gp_PntData(gp_Pnt const point)
		: _point(point)
	{}

	gp_PntData(Standard_Real x, Standard_Real y, Standard_Real z) {
		_point.SetX(x);
		_point.SetY(y);
		_point.SetZ(z);
	}

	NodeDataType type() const override
	{
		return NodeDataType{ "point",
			"Point" };
	}

	gp_Pnt point() const
	{
		return _point;
	}

private:

	gp_Pnt _point;
};

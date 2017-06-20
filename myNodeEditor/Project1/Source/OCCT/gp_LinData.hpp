#pragma once

#include <nodes/NodeDataModel>
#include <gp_Lin.hxx>
#include <gce_MakeLin.hxx>


using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class gp_LinData : public NodeData
{
public:

	gp_LinData()
		: _lin()
	{}

	gp_LinData(gp_Lin const lin)
		: _lin(lin)
	{}

	gp_LinData(gp_Pnt const p1, gp_Pnt const p2) {
		_lin = gce_MakeLin::gce_MakeLin(p1, p2);
	}

	NodeDataType type() const override
	{
		return NodeDataType{ "lin",
			"Lin" };
	}

	gp_Lin lin() const
	{
		return _lin;
	}

private:

	gp_Lin _lin;
};

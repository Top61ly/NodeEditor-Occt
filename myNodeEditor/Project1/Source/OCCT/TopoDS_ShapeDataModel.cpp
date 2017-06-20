#include "gp_PntData.hpp"
#include "TopoDS_ShapeData.hpp"

#include "TopoDS_ShapeDataModel.hpp"

unsigned int
TopoDS_ShapeDataModel::
nPorts(PortType portType) const
{
	unsigned int result;

	if (portType == PortType::In)
		result = 1;
	else
		result = 1;

	return result;
}


NodeDataType
TopoDS_ShapeDataModel::
dataType(PortType porttype, PortIndex) const
{
	if (porttype == PortType::In)
		return DecimalData().type();
	else
	{
		return TopoDS_ShapeData().type();
	}
}


std::shared_ptr<NodeData>
TopoDS_ShapeDataModel::
outData(PortIndex)
{
	return std::static_pointer_cast<NodeData>(_result);
}


void
TopoDS_ShapeDataModel::
setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
	auto numberData =
		std::dynamic_pointer_cast<DecimalData>(data);

	if (portIndex == 0)
	{
		_number = numberData;
	}

	double n1 = _number.lock()->number();

	if (n1 > 0) {
		gp_Ax2 anAxis;
		anAxis.SetLocation(gp_Pnt(0.0, 0.0, 0.0));

		TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, n1).Shape();
		modelValidationState = NodeValidationState::Valid;
		modelValidationError = QString();
		_result = std::make_shared<TopoDS_ShapeData>(aTopoSphere);
	}
	else
	{
		modelValidationState = NodeValidationState::Error;
		modelValidationError = QString("input < 0");
	}
}


NodeValidationState
TopoDS_ShapeDataModel::
validationState() const
{
	return modelValidationState;
}


QString
TopoDS_ShapeDataModel::
validationMessage() const
{
	return modelValidationError;
}

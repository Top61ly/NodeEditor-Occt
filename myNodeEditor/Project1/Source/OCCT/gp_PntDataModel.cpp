#include "gp_PntDataModel.hpp"

#include "gp_PntData.hpp"

unsigned int
gp_PntDataModel::
nPorts(PortType portType) const
{
	unsigned int result;

	if (portType == PortType::In)
		result = 3;
	else
		result = 1;

	return result;
}


NodeDataType
gp_PntDataModel::
dataType(PortType portType, PortIndex) const
{
	if (portType == PortType::In)
	return DecimalData().type();
	else
	{
		return gp_PntData().type();
	}
}


std::shared_ptr<NodeData>
gp_PntDataModel::
outData(PortIndex)
{
	return std::static_pointer_cast<NodeData>(_result);
}


void
gp_PntDataModel::
setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
	auto numberData =
		std::dynamic_pointer_cast<DecimalData>(data);

	if (portIndex == 0)
	{
		_numberx = numberData;
	}
	if (portIndex == 1)
	{
		_numbery = numberData;
	}
	if (portIndex == 2)
	{
		_numberz = numberData;
	}

	setdata();
}


NodeValidationState
gp_PntDataModel::
validationState() const
{
	return modelValidationState;
}


QString
gp_PntDataModel::
validationMessage() const
{
	return modelValidationError;
}

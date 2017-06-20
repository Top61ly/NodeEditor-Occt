#include "gp_PntData.hpp"
#include "gp_LinData.hpp"

#include "gp_MakeLinModel.hpp"

unsigned int
gp_MakeLinModel::
nPorts(PortType portType) const
{
	unsigned int result;

	if (portType == PortType::In)
		result = 2;
	else
		result = 1;

	return result;
}


NodeDataType
gp_MakeLinModel::
dataType(PortType porttype, PortIndex) const
{
	if (porttype == PortType::In)
		return gp_PntData().type();
	else
	{
		return gp_LinData().type();
	}
}


std::shared_ptr<NodeData>
gp_MakeLinModel::
outData(PortIndex)
{
	return std::static_pointer_cast<NodeData>(_result);
}


void
gp_MakeLinModel::
setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
	auto numberData =
		std::dynamic_pointer_cast<gp_PntData>(data);

	if (portIndex == 0)
	{
		_number1 = numberData;
	}
	else
	{
		_number2 = numberData;
	}

	CADcompute();
}


NodeValidationState
gp_MakeLinModel::
validationState() const
{
	return modelValidationState;
}


QString
gp_MakeLinModel::
validationMessage() const
{
	return modelValidationError;
}

#include "gp_PntData.hpp"
#include "TopoDS_ShapeData.hpp"
#include "mainwidget.hpp"
#include "DisplayModel.hpp"

unsigned int
 DisplayModel::
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
 DisplayModel::
dataType(PortType porttype, PortIndex) const
{
	if (porttype == PortType::In)
		return TopoDS_ShapeData().type();
	else
	{
		return DecimalData().type();
	}
}


std::shared_ptr<NodeData>
 DisplayModel::
outData(PortIndex)
{
	return std::static_pointer_cast<NodeData>(_result);
}


void
 DisplayModel::
setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
	auto shapeData =
		std::dynamic_pointer_cast<TopoDS_ShapeData>(data);

	if (portIndex == 0)
	{
		_shape = shapeData;
	}
	auto s1 = _shape.lock();
	
	if (s1) {
		TopoDS_Shape shape = s1->shape();

		if (shape.IsNull()) {
			//occqt->addNewShapeFromNodeEditor();
			modelValidationState = NodeValidationState::Error;
			modelValidationError = QString("shape is null");
		}
		else
		{

			AllShapes::addShape(shape);
			modelValidationState = NodeValidationState::Valid;
			modelValidationError = QString();
		}
	}
}


NodeValidationState
 DisplayModel::
validationState() const
{
	return modelValidationState;
}


QString
 DisplayModel::
validationMessage() const
{
	return modelValidationError;
}

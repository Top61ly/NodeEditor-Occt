#pragma once

#include <QtCore/QObject>
#include <QtCore/QJsonObject>
#include <QtWidgets/QLabel>

#include <nodes/NodeDataModel>

#include <iostream>
#include <list>

#include <BRepPrimAPI_MakeSphere.hxx>

#include "TopoDS_ShapeData.hpp"
#include "DecimalData.hpp"

#include "AllShapes.h"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;


/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class  DisplayModel : public NodeDataModel
{
	Q_OBJECT;
public:
	DisplayModel(){}
	virtual
		~DisplayModel() {}

public:

	QString
		caption() const override
	{
		return QStringLiteral("Display");
	}

	QString
		name() const override
	{
		return QStringLiteral("Display");
	}

	bool
		portCaptionVisible(PortType, PortIndex) const override
	{
		return true;
	}

	QString
		portCaption(PortType portType, PortIndex portIndex) const override
	{
		switch (portType)
		{
		case PortType::In:

			return QStringLiteral("in");

			break;

		case PortType::Out:
			return QStringLiteral("out");

		default:
			break;
		}
		return QString();
	}

	std::unique_ptr<NodeDataModel>
		clone() const override
	{
		return std::make_unique<DisplayModel>();
	}

private:
	unsigned int
		nPorts(PortType portType) const override;

	NodeDataType
		dataType(PortType portType,
			PortIndex portIndex) const override;

	std::shared_ptr<NodeData>
		outData(PortIndex port) override;

	void
		setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override;

	QWidget *
		embeddedWidget() override { return nullptr; }

	NodeValidationState
		validationState() const override;

	QString
		validationMessage() const override;

protected:

	std::weak_ptr<TopoDS_ShapeData> _shape;

	std::shared_ptr<DecimalData> _result;

	NodeValidationState modelValidationState = NodeValidationState::Warning;
	QString modelValidationError = QString("Missing or incorrect inputs");

};

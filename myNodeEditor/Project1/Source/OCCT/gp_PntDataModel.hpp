#pragma once

#include <QtCore/QObject>
#include <QtCore/QJsonObject>
#include <QtWidgets/QLabel>

#include <nodes/NodeDataModel>

#include <iostream>

#include "DecimalData.hpp"
#include "gp_PntData.hpp"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class gp_PntDataModel : public NodeDataModel
{
	Q_OBJECT;
public:

	virtual
		~gp_PntDataModel() {}

public:

	QString caption() const override 
	{ return QStringLiteral("gp_Point");}

	bool
		captionVisible() const override
	{
		return true;
	}

	QString name() const override
	{
		return QStringLiteral("gp_Point");
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
			if (portIndex == 0)
				return QStringLiteral("pointX");
			else if (portIndex == 1)
				return QStringLiteral("pointY");
			else if (portIndex == 2)
				return QStringLiteral("pointZ");
			
			break;

		case PortType::Out:
			return QStringLiteral("Point");

		default:
			break;
		}
		return QString();
	}

	std::unique_ptr<NodeDataModel> clone() const override
	{
		return std::make_unique<gp_PntDataModel>();
	}

public:
		
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
	
	virtual
	void setdata()
	{
		PortIndex const outPortIndex = 0;

		auto n1 = _numberx.lock();
		auto n2 = _numbery.lock();
		auto n3 = _numberz.lock();

		if (n1 && n2 && n3) {
			modelValidationState = NodeValidationState::Valid;
			modelValidationError = QString();
			_result = std::make_shared<gp_PntData>(n1->number(),n2->number(),n3->number());
		}
		else
		{
			modelValidationState = NodeValidationState::Warning;
			modelValidationError = QStringLiteral("Missing or incorrect inputs");
			_result.reset();
		}

		emit dataUpdated(outPortIndex);
	}

private:
	std::weak_ptr<DecimalData> _numberx;
	std::weak_ptr<DecimalData> _numbery;
	std::weak_ptr<DecimalData> _numberz;

	std::shared_ptr<gp_PntData> _result;

	NodeValidationState modelValidationState = NodeValidationState::Warning;
	QString modelValidationError = QString("Missing or incorrect inputs");
};

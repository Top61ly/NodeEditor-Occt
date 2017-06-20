#pragma once

#include <QtCore/QObject>
#include <QtCore/QJsonObject>
#include <QtWidgets/QLabel>

#include <nodes/NodeDataModel>

#include <iostream>

#include "gp_PntData.hpp"
#include "gp_LinData.hpp"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class gp_MakeLinModel : public NodeDataModel
{
	Q_OBJECT;
public:

	virtual
		~gp_MakeLinModel() {}

public:

	QString
		caption() const override
	{
		return QStringLiteral("gp_MakeLin");
	}

	QString
		name() const override
	{
		return QStringLiteral("gp_MakeLin");
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
				return QStringLiteral("point 1");
			else if (portIndex == 1)
				return QStringLiteral("point 2");
			break;

		case PortType::Out:
			return QStringLiteral("Lin");

		default:
			break;
		}
		return QString();
	}

	std::unique_ptr<NodeDataModel>
		clone() const override
	{
		return std::make_unique<gp_MakeLinModel>();
	}

private:

	void
		CADcompute() 
	{
		PortIndex const outPortIndex = 0;

		auto n1 = _number1.lock();
		auto n2 = _number2.lock();

		if (n1 && n2 &&(n1 != n2))
		{
			modelValidationState = NodeValidationState::Valid;
			modelValidationError = QString();
			_result = std::make_shared<gp_LinData>(n1->point(),n2->point());
		}
		else
		{
			modelValidationState = NodeValidationState::Warning;
			if (n1 == n2)
				modelValidationError = QStringLiteral("两个点一样");
			else
				modelValidationError = QStringLiteral("缺少输入或者输入错误");
			
			_result.reset();
		}

		emit dataUpdated(outPortIndex);
	}
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

	std::weak_ptr<gp_PntData> _number1;
	std::weak_ptr<gp_PntData> _number2;

	std::shared_ptr<gp_LinData> _result;

	NodeValidationState modelValidationState = NodeValidationState::Warning;
	QString modelValidationError = QString("Missing or incorrect inputs");


};

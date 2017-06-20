#pragma once
#include <QObject>
#include <QtWidgets>
#include <QMainWindow>
#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>

#include "occqt.hpp"
#include <nodes/DataModelRegistry>

#include "Number.h"
#include "gp_PntDataModel.hpp"
#include "gp_MakeLinModel.hpp"
#include "TopoDS_ShapeDataModel.hpp"
#include "DisplayModel.hpp"
#include <vector>

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;


class MainWidget : public QWidget {
	Q_OBJECT;

public:
	MainWidget(QWidget * parent = Q_NULLPTR);
	~MainWidget();
private:
	static std::shared_ptr<DataModelRegistry> registerDataModels();
	static void setStyle();

private:
	FlowView *flowview;
    occQt *occqt;
	std::vector<TopoDS_Shape> myShapeModel;
};

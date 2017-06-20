#include "mainwidget.hpp"

MainWidget::MainWidget(QWidget * parent) : QWidget(parent){
	
	QHBoxLayout *lh = new QHBoxLayout;
	QVBoxLayout *l = new QVBoxLayout;
    auto menuBar = new QMenuBar;	
	auto saveAction = menuBar->addAction("Save..");
	auto loadAction = menuBar->addAction("Load..");
	auto BuildAction = menuBar->addAction("Build(Test)");
	l->addWidget(menuBar);

	occqt = new occQt();
	auto scene = new FlowScene(registerDataModels());
	flowview = new FlowView(scene);
	
	l->setContentsMargins(0, 0, 0, 0);
	l->setSpacing(0);
	
	lh->addWidget(flowview);
	lh->addWidget(occqt);
	lh->setContentsMargins(0, 0, 0, 0); 
	lh->setSpacing(0);

	l->addLayout(lh);

	QObject::connect(saveAction, &QAction::triggered,
		scene, &FlowScene::save);

	QObject::connect(loadAction, &QAction::triggered,
		scene, &FlowScene::load);

	QObject::connect(BuildAction, &QAction::triggered,
		occqt, &occQt::addNewShapeFromNodeEditor);


	setLayout(l);
	setWindowTitle("Dataflow tools: simplest calculator");
	resize(1024, 768);
	showNormal();
}


MainWidget::~MainWidget() {
	
}


std::shared_ptr<DataModelRegistry>
MainWidget::registerDataModels() {
	auto ret = std::make_shared<DataModelRegistry>();
	//ret->registerModel<displayModel>();
	ret->registerModel<gp_PntDataModel>("OCCT");
	ret->registerModel<gp_MakeLinModel>("OCCT");
	ret->registerModel<TopoDS_ShapeDataModel>("OCCT");

	ret->registerModel<DisplayModel>();
#pragma region Simple Calculator
	ret->registerModel<NumberSourceDataModel>("Sources");

	ret->registerModel<NumberDisplayDataModel>("Displays");

	ret->registerModel<AdditionModel>("Operators");

	ret->registerModel<SubtractionModel>("Operators");

	ret->registerModel<MultiplicationModel>("Operators");

	ret->registerModel<DivisionModel>("Operators");

	ret->registerModel<ModuloModel>("Operators");

	ret->registerModel<DecimalToIntegerModel, true>("Type converters");

	ret->registerModel<IntegerToDecimalModel, true>("Type converters");

#pragma endregion



	return ret;
}

void MainWidget::setStyle() {
	ConnectionStyle::setConnectionStyle(
		R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");
}

//-------------------------------------------------------------------------------------------
//  University of Victoria Computer Science Department 
//	FrameWork for OpenGL application under QT
//  Course title: Computer Graphics CSC305
//-------------------------------------------------------------------------------------------
#include <QtGui>
#include <QtOpenGL>

#include "glwidget.h"
#include "window.h"


//------------------------------------------------------------------------------------
// Creates and initializes the main window for application
//------------------------------------------------------------------------------------
Window::Window(QWidget *parent):QDialog(parent)
{
	//We create an instance of GLWidget component we built in glwidget.h
	m_glWidget = new GLWidget;

	//Setup application interface. Creates all the required components and sliders.
	setupUi(this);

	//We need to attach our m_glWidget to glWidgetArea
	//All our drawings will be on glWidgetArea
	glWidgetArea->setWidget(m_glWidget);

	//Setting up all the SIGNALS and SLOTS
	connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(btnReset, SIGNAL(clicked()), m_glWidget, SLOT(reset()));
	connect(chkPerspective, SIGNAL(clicked(bool)), m_glWidget, SLOT(setView(bool)));

	connect(sectorSlider, SIGNAL(valueChanged(int)), m_glWidget, SLOT(setSectors(int)));
	connect(stackSlider, SIGNAL(valueChanged(int)), m_glWidget, SLOT(setStacks(int)));
	connect(seRadiusStart, SIGNAL(valueChanged(double)), m_glWidget, SLOT(setRadiusStart(double)));
	connect(seRadiusEnd, SIGNAL(valueChanged(double)), m_glWidget, SLOT(setRadiusEnd(double)));

	connect(chkSurface, SIGNAL(clicked(bool)), m_glWidget, SLOT(setDrawSurface(bool)));
	connect(chkWireFrame, SIGNAL(clicked(bool)), m_glWidget, SLOT(setDrawWireFrame(bool)));
	connect(chkCrossSections, SIGNAL(clicked(bool)), m_glWidget, SLOT(setDrawCrossSections(bool)));
        connect(chkDrawNormals, SIGNAL(clicked(bool)), m_glWidget, SLOT(setDrawNormals(bool)));

        connect(btnCloseCurve, SIGNAL(clicked()), m_glWidget, SLOT(closeCurve()));
        connect(btnExportModel, SIGNAL(clicked()), m_glWidget, SLOT(exportModel()));

	/*   Connect extra signal/slots here like:
	connect(btnRunAnimation, SIGNAL(clicked()), m_glWidget, SLOT(startAnimation())); 
	connect(btnStopAnimation, SIGNAL(clicked()), m_glWidget, SLOT(stopAnimation())); 
	connect(udX, SIGNAL(valueChanged(double)), m_glWidget, SLOT(selXChanged(double)));
	connect(udY, SIGNAL(valueChanged(double)), m_glWidget, SLOT(selYChanged(double)));
	*/
}

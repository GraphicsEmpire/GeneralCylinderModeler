/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Sat Jul 16 15:08:45 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QToolBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmMain
{
public:
    QHBoxLayout *horizontalLayout;
    QScrollArea *glWidgetArea;
    QWidget *scrollAreaWidgetContents;
    QToolBox *toolBox;
    QWidget *tsSettings;
    QGroupBox *groupBox;
    QPushButton *btnClose;
    QPushButton *btnReset;
    QLCDNumber *lcdNumber_2;
    QLabel *label_3;
    QDoubleSpinBox *seRadiusStart;
    QLabel *label;
    QSlider *sectorSlider;
    QLCDNumber *lcdNumber;
    QLabel *label_2;
    QSlider *stackSlider;
    QLabel *label_4;
    QDoubleSpinBox *seRadiusEnd;
    QGroupBox *groupBox_2;
    QCheckBox *chkWireFrame;
    QCheckBox *chkPerspective;
    QCheckBox *chkSurface;
    QCheckBox *chkCrossSections;
    QCheckBox *chkDrawNormals;
    QPushButton *btnCloseCurve;
    QWidget *tsExport;
    QPushButton *btnExportModel;

    void setupUi(QWidget *frmMain)
    {
        if (frmMain->objectName().isEmpty())
            frmMain->setObjectName(QString::fromUtf8("frmMain"));
        frmMain->resize(835, 548);
        horizontalLayout = new QHBoxLayout(frmMain);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        glWidgetArea = new QScrollArea(frmMain);
        glWidgetArea->setObjectName(QString::fromUtf8("glWidgetArea"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(glWidgetArea->sizePolicy().hasHeightForWidth());
        glWidgetArea->setSizePolicy(sizePolicy);
        glWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        glWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        glWidgetArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 579, 528));
        glWidgetArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(glWidgetArea);

        toolBox = new QToolBox(frmMain);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolBox->sizePolicy().hasHeightForWidth());
        toolBox->setSizePolicy(sizePolicy1);
        toolBox->setMinimumSize(QSize(230, 530));
        tsSettings = new QWidget();
        tsSettings->setObjectName(QString::fromUtf8("tsSettings"));
        tsSettings->setGeometry(QRect(0, 0, 230, 476));
        groupBox = new QGroupBox(tsSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 231, 471));
        btnClose = new QPushButton(groupBox);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(150, 440, 75, 23));
        btnReset = new QPushButton(groupBox);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));
        btnReset->setGeometry(QRect(60, 440, 75, 23));
        lcdNumber_2 = new QLCDNumber(groupBox);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(160, 89, 51, 20));
        lcdNumber_2->setNumDigits(3);
        lcdNumber_2->setProperty("value", QVariant(2));
        lcdNumber_2->setProperty("intValue", QVariant(2));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 140, 71, 16));
        seRadiusStart = new QDoubleSpinBox(groupBox);
        seRadiusStart->setObjectName(QString::fromUtf8("seRadiusStart"));
        seRadiusStart->setGeometry(QRect(91, 140, 121, 22));
        seRadiusStart->setSingleStep(0.01);
        seRadiusStart->setValue(0.25);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 36, 16));
        sectorSlider = new QSlider(groupBox);
        sectorSlider->setObjectName(QString::fromUtf8("sectorSlider"));
        sectorSlider->setGeometry(QRect(52, 40, 101, 19));
        sectorSlider->setMinimum(3);
        sectorSlider->setMaximum(30);
        sectorSlider->setOrientation(Qt::Horizontal);
        lcdNumber = new QLCDNumber(groupBox);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(160, 40, 51, 20));
        lcdNumber->setNumDigits(3);
        lcdNumber->setProperty("value", QVariant(3));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 90, 31, 16));
        stackSlider = new QSlider(groupBox);
        stackSlider->setObjectName(QString::fromUtf8("stackSlider"));
        stackSlider->setGeometry(QRect(52, 90, 101, 19));
        stackSlider->setMinimum(2);
        stackSlider->setMaximum(1000);
        stackSlider->setValue(2);
        stackSlider->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 182, 71, 16));
        seRadiusEnd = new QDoubleSpinBox(groupBox);
        seRadiusEnd->setObjectName(QString::fromUtf8("seRadiusEnd"));
        seRadiusEnd->setGeometry(QRect(91, 180, 121, 22));
        seRadiusEnd->setSingleStep(0.01);
        seRadiusEnd->setValue(0.25);
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 219, 201, 181));
        chkWireFrame = new QCheckBox(groupBox_2);
        chkWireFrame->setObjectName(QString::fromUtf8("chkWireFrame"));
        chkWireFrame->setGeometry(QRect(10, 60, 131, 18));
        chkWireFrame->setChecked(true);
        chkPerspective = new QCheckBox(groupBox_2);
        chkPerspective->setObjectName(QString::fromUtf8("chkPerspective"));
        chkPerspective->setGeometry(QRect(10, 30, 121, 18));
        chkSurface = new QCheckBox(groupBox_2);
        chkSurface->setObjectName(QString::fromUtf8("chkSurface"));
        chkSurface->setGeometry(QRect(10, 120, 131, 18));
        chkCrossSections = new QCheckBox(groupBox_2);
        chkCrossSections->setObjectName(QString::fromUtf8("chkCrossSections"));
        chkCrossSections->setGeometry(QRect(10, 90, 131, 18));
        chkCrossSections->setChecked(true);
        chkDrawNormals = new QCheckBox(groupBox_2);
        chkDrawNormals->setObjectName(QString::fromUtf8("chkDrawNormals"));
        chkDrawNormals->setGeometry(QRect(10, 150, 121, 18));
        btnCloseCurve = new QPushButton(groupBox);
        btnCloseCurve->setObjectName(QString::fromUtf8("btnCloseCurve"));
        btnCloseCurve->setGeometry(QRect(60, 410, 75, 23));
        toolBox->addItem(tsSettings, QString::fromUtf8("Model Settings"));
        tsExport = new QWidget();
        tsExport->setObjectName(QString::fromUtf8("tsExport"));
        tsExport->setGeometry(QRect(0, 0, 230, 476));
        btnExportModel = new QPushButton(tsExport);
        btnExportModel->setObjectName(QString::fromUtf8("btnExportModel"));
        btnExportModel->setGeometry(QRect(30, 20, 141, 23));
        toolBox->addItem(tsExport, QString::fromUtf8("Export"));

        horizontalLayout->addWidget(toolBox);


        retranslateUi(frmMain);
        QObject::connect(sectorSlider, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(stackSlider, SIGNAL(valueChanged(int)), lcdNumber_2, SLOT(display(int)));

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(frmMain);
    } // setupUi

    void retranslateUi(QWidget *frmMain)
    {
        frmMain->setWindowTitle(QApplication::translate("frmMain", "Pourya Shirazian - Computer Graphics LAB FrameWork", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("frmMain", "Tool Box", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("frmMain", "Close", 0, QApplication::UnicodeUTF8));
        btnReset->setText(QApplication::translate("frmMain", "reset", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("frmMain", "Radius Start:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("frmMain", "Sectors", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("frmMain", "Stacks", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("frmMain", "Radius End:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("frmMain", "Display", 0, QApplication::UnicodeUTF8));
        chkWireFrame->setText(QApplication::translate("frmMain", "Draw WireFrame", 0, QApplication::UnicodeUTF8));
        chkPerspective->setText(QApplication::translate("frmMain", "Perspective View", 0, QApplication::UnicodeUTF8));
        chkSurface->setText(QApplication::translate("frmMain", "Draw Surface", 0, QApplication::UnicodeUTF8));
        chkCrossSections->setText(QApplication::translate("frmMain", "Draw Cross Sections", 0, QApplication::UnicodeUTF8));
        chkDrawNormals->setText(QApplication::translate("frmMain", "Draw Normals", 0, QApplication::UnicodeUTF8));
        btnCloseCurve->setText(QApplication::translate("frmMain", "Close Curve", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(tsSettings), QApplication::translate("frmMain", "Model Settings", 0, QApplication::UnicodeUTF8));
        btnExportModel->setText(QApplication::translate("frmMain", "Export Model Settings", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(tsExport), QApplication::translate("frmMain", "Export", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class frmMain: public Ui_frmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

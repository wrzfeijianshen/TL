package ui

import (
	"fmt"

	"github.com/kitech/qt.go/qtcore"
	"github.com/kitech/qt.go/qtwidgets"
)

func init() { qtcore.KeepMe() }
func init() { qtwidgets.KeepMe() } // 调用时初始化

type Ui_MainWindow struct {
	Centralwidget *qtwidgets.QWidget
	MainWindow    *qtwidgets.QMainWindow
	Label         *qtwidgets.QLabel
	Dialog        *qtwidgets.QDialog
}

func NewUi_MainWindow() *Ui_MainWindow {
	return &Ui_MainWindow{}
}
func (this *Ui_MainWindow) SetupUi(MainWindow *qtwidgets.QMainWindow) {
	this.MainWindow = MainWindow
	if MainWindow.ObjectName() == "" {
		fmt.Println("MainWindow ObjectName 为空")
		MainWindow.SetObjectName("MainWindow")
	}

	// 在MainWindow 创建QWidget
	this.Centralwidget = qtwidgets.NewQWidget(this.MainWindow, 0) // 111
	this.Centralwidget.SetObjectName("Centralwidget")             // 112
	// 这两步一般是组合使用

	this.Label = qtwidgets.NewQLabel(this.Centralwidget, 0) // 111
	this.Label.SetObjectName("Label")                       // 112
	// this.Label.SetContentsMargins(50, 50, 100, 100)

}
func (this *Ui_MainWindow) RetranslateUi(MainWindow *qtwidgets.QMainWindow) {
	MainWindow.SetWindowTitle("MainWindow")
	// MainWindow.SetFixedSize_1(500, 500)
	MainWindow.Resize(500, 500)
	MainWindow.Move(0, 0)

	// this.Centralwidget.SetFixedSize_1(500,500)
	this.Label.SetText("hello哈哈")

	// this.Label.SetContentsMargins(100, 100, 100, 100)
	// this.Label.SetFixedSize_1(100, 100)
	// this.Label.Move(20, 20)

	this.Label.SetGeometry(10, 10, 80, 80)
}
func NewUi_MainWindow2() *Ui_MainWindow {
	this := &Ui_MainWindow{}
	// w := qtwidgets.NewQMainWindow(nil, 0) // 创建QMainWindow
	w := qtwidgets.NewQMainWindow(nil, 0)
	this.SetupUi(w)                     // 设置控件UI，名称
	this.RetranslateUi(this.MainWindow) // 设置控件属性

	qtcore.QMetaObject_ConnectSlotsByName(this.MainWindow) // 100111

	return this
}
func (this *Ui_MainWindow) Show() {
	this.MainWindow.Show()
}

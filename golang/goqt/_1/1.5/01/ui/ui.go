package ui

import (
	"fmt"

	"github.com/kitech/qt.go/qtwidgets"
)

func init() { qtwidgets.KeepMe() } // 调用时初始化

type Ui_MainWindow struct {
	Centralwidget *qtwidgets.QWidget
	MainWindow    *qtwidgets.QMainWindow
}

func NewUi_MainWindow() *Ui_MainWindow {
	return &Ui_MainWindow{}
}
func (this *Ui_MainWindow) SetupUi(MainWindow *qtwidgets.QMainWindow) {
	this.MainWindow = MainWindow
	if MainWindow.ObjectName() == "" {
		fmt.Println("MainWindow ObjectName 为空")
		// MainWindow.SetObjectName("MainWindow")
		MainWindow.SetWindowTitle("MainWindow")
	}
	MainWindow.Resize(300, 200)
}

func NewUi_MainWindow2() *Ui_MainWindow {
	this := &Ui_MainWindow{}
	w := qtwidgets.NewQMainWindow(nil, 0) // 创建QMainWindow
	this.SetupUi(w)

	return this
}
func (this *Ui_MainWindow) Show() {
	this.MainWindow.Show()
}

package main

import (
	"os"

	"github.com/kitech/qt.go/qtwidgets"
)

func main() {
	app := qtwidgets.NewQApplication(len(os.Args), os.Args, 0)
	// A()
	mw := NewUi_Form2()
	// mw.QWidget.Show()
	mw.Form.Show()
	app.Exec()
}

package main

import (
	"os"

	"github.com/kitech/qt.go/qtwidgets"
	"github.com/wrzfeijianshen/TL/golang/goqt/_1/1.5/02/ui"
)

func main() {
	app := qtwidgets.NewQApplication(len(os.Args), os.Args, 0)
	mw := ui.NewUi_MainWindow2()
	mw.Show()
	app.SetApplicationName("222")
	app.Exec()
}

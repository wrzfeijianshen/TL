package main

import (
	"fmt"
	"os"

	"github.com/kitech/qt.go/qtcore"

	"github.com/kitech/qt.go/qtwidgets"
)

func main() {
	// qtrt.SetDebugFFICall(true)

	argv := os.Args
	// app := qtcore.NewQCoreApplication(len(argv), argv, 0)
	app := qtwidgets.NewQApplication(len(argv), argv, 0)
	mw := qtwidgets.NewQMainWindow(nil, 0)
	mw.SetFixedSize_1(200, 200)

	txt := qtcore.NewQString_5("hehehg呵呵")
	fmt.Println(txt.ToLocal8Bit().Data())

	mw.Show()
	app.Exec() // 保证程序5秒后结束
}

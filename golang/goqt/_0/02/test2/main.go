package main

import (
	"fmt"
	"os"
	"time"

	"github.com/kitech/qt.go/qtwidgets"
)

func main() {
	// qtrt.SetDebugFFICall(true)

	argv := os.Args
	// app := qtcore.NewQCoreApplication(len(argv), argv, 0)
	app := qtwidgets.NewQApplication(len(argv), argv, 0)
	mw := qtwidgets.NewQMainWindow(nil, 0)
	mw.SetFixedSize_1(200, 200)
	mw.Show()

	// a := qtwidgets.NewQWidget(nil, 0) // 创建widge窗口
	// a.SetFixedSize_1(200, 200)        // 设置大小
	// a.Show()                          // 需要显示

	go func() {
		time.Sleep(5 * time.Second)
		fmt.Println("程序结束了")
		app.Exit(0)
	}()
	app.Exec() // 保证程序5秒后结束
}

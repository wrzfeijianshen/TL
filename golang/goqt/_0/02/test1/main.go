package main

import (
	"fmt"
	"os"
	"time"

	"github.com/kitech/qt.go/qtwidgets"
)

func main() {
	argv := os.Args
	app := qtwidgets.NewQApplication(len(argv), argv, 0)
	app.SetApplicationName("窗口") // 设置应用程序名字

	a := qtwidgets.NewQWidget(nil, 0) // 创建widge窗口
	// a.SetFixedSize_1(200, 200)        // 设置大小
	a.Resize(200,200)
	a.Show()                          // 需要显示
	go func() {
		time.Sleep(5 * time.Second)
		fmt.Println("程序结束了")
		app.Exit(0)
	}()
	app.Exec() // 保证程序5秒后结束
}

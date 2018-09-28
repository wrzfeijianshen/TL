package main

import (
	"github.com/kitech/qt.go/qtwidgets"
)

func main() {
	argv := []string{"./guiapp", "-v", "-x"}
	app := qtwidgets.NewQApplication(len(argv), argv, 0)
	app.SetApplicationName("窗口")      // 设置应用程序名字
	a := qtwidgets.NewQWidget(nil, 0) // 创建widge窗口
	a.SetFixedSize_1(200, 200)        // 设置大小
	a.Show()// 需要显示
	app.Exec()
}

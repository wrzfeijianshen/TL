package main

import (
	"os"

	"github.com/therecipe/qt/widgets"
)

func main() {
	// 在开始使用QWidgets之前需要被调用一次
	app := widgets.NewQApplication(len(os.Args), os.Args)

	// 创建窗口
	window := widgets.NewQMainWindow(nil, 0)

	// 设置大小
	window.SetMinimumSize2(500, 500)

	// 设置窗口标题
	window.SetWindowTitle("hello window")

	// 默认窗口是隐藏的，需要显示出来
	window.Show()
	app.Exec()
}

#include <iostream>
#include <boost/timer.hpp>
#include <windows.h>
int main()
{
    system("chcp 65001");// 设置编码输出为中文
    std::cout << "===中文===" << std::endl;
    boost::timer t;
    std::cout << CLOCKS_PER_SEC << std::endl;
    // 开头为_特殊字符，直接中文会打印不出来，不知为什么，所以以后都是这样以_开头为中文
    std::cout << "_最大时间:" << t.elapsed_max() /3600  << " h" << std::endl;
    std::cout << "_最小时间: " << t.elapsed_min() << " s" << std::endl;
    std::cout << "_现在流逝时间: " << t.elapsed() << " s" << std::endl;
    Sleep(1000);
    std::cout << "_现在流逝时间: " << t.elapsed() << " s" << std::endl;
    return 0;
}

#include <iostream>
#include <boost/math/special_functions/acosh.hpp>
#include <boost/math/special_functions/bessel.hpp>

#include <string>
#include <boost/filesystem.hpp>
#include <boost/timer.hpp>

using namespace boost::math;
using namespace boost::math::detail;
namespace fs = boost::filesystem;

//测试boost贝塞尔函数
void testBessel(){
    std::cout<<"Test Boost:"<<std::endl;

    std::cout<<acosh(2.5)<<std::endl;

    std::cout<<bessel_i0(3.2)<<std::endl;

    std::cout<<"Test Finished!"<<std::endl;
}

int main(int argc, char *argv[])
{

    std::cout << "-----测试boost贝塞尔函数-------" << std::endl;
    testBessel();
    return 0;
}


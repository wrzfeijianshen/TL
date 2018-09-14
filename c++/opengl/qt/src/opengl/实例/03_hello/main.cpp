#include "gl_win.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GL_Win w;
    w.show();

    return a.exec();
}

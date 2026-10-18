#include <QApplication>
#include "SearchWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SearchWindow window;
    window.show();

    return app.exec();
}
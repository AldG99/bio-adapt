#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("Simulador de Tardígrados");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("BioAdapt");
    app.setApplicationDisplayName("🐻‍❄️ Simulador de Tardígrados");
    
    // Set application icon if available
    // app.setWindowIcon(QIcon(":/icon.png"));
    
    // Create and show main window
    MainWindow window;
    window.show();
    
    return app.exec();
}
#pragma region INCLUDES
#pragma comment(lib, "Ws2_32.lib")//add this library for getnameinfo()
#include "qapplication"
#include "mainwindow.h"
#include <iostream>
#ifdef max//get rid of max  macro so we can use numerical_limits<>::max if needed
#undef max
#endif
#pragma endregion

int main(int argc, char** argv)
try {
	QApplication app{ argc, argv };
	MainWindow window{};
	window.show();
	return app.exec();
}
catch (std::exception& e) {
	std::cerr << "In MAIN(), exception handled in catch(std::exception& e)" << std::endl
		<< "Error msg: " << e.what() << std::endl;
}
catch (...) {
	std::cerr << "Unhandled exception!  Unkown type " << std::endl;
}


//PROBLEMs:
//json file doesnt save if program gets force shut because destructor doesnt get called
//widget insert row in aliases doesnt update properly when viewport is filled
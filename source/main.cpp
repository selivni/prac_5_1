#include "Cellurar.hpp"
#include "InfoStorage.hpp"
#include "Graphics.hpp"


int main(int argc, char** argv)
{
	char mesa_version_override[]="MESA_GL_VERSION_OVERRIDE=3.3COMPAT";
	putenv(mesa_version_override);
	try
	{
		InfoStorage storage;
		storage.GetInfo();
		Graphics graphical_controller(storage, &argc, argv);
		ThisIsAVeryBadIdeaButOhWellIHaveToDoItCuzOfFuckingStandard = &graphical_controller;
		graphical_controller.InitGlut();
		graphical_controller.InitGlew();
		graphical_controller.CreateField();
		graphical_controller.MainLoop();
	}
	catch (string s)
	{
		cout << s << endl;
	}
	return 0;
}

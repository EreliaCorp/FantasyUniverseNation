#include "jgl.h"

#include "widget/fun_main_application.h"

int main()
{
	jgl::Application app("Fantasy Universe Nation", jgl::Vector2Int(840, 680), jgl::Color(0, 0, 0));
	app.set_default_font("ressource/font/karma suture.ttf");
	app.active_multithread();

	fun::MainApplication main_app = fun::MainApplication(nullptr);
	main_app.set_geometry(0, app.size());
	main_app.activate();

	return (app.run());
}
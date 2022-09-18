#include "jgl.h"

#include "widget/MainApplication/fun_main_application.h"

int main()
{
	jgl::Application app("Fantasy Universe Nation", jgl::Vector2Int(840, 680), jgl::Color(0, 0, 0));
	app.set_default_font("ressource/font/karma suture.ttf");
	app.active_multithread();

	fun::MainApplication::instanciate(nullptr);
	fun::MainApplication::instance()->set_geometry(0, app.size());
	fun::MainApplication::instance()->activate();

	return (app.run());
}
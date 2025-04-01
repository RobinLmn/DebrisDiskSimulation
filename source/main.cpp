#include "engine/core/log.hpp"

#include "application/application.hpp"

int main()
{
	engine::logger::initialize();

	application app;
	app.run();

	return 0;
}
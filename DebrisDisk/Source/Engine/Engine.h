#pragma once

namespace DebrisDisk
{
	class Engine
	{
	public:
		static Engine& GetEngine() { static Engine Engine; return Engine; }
		void Run();

		Engine(Engine& e) = delete;
		void operator=(const Engine& e) = delete;

	private:
		Engine() = default;

	private:
		bool bRunning = true;
	};
}

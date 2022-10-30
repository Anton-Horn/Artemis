#pragma once


	class Application {

	public:

		static Application* Create();
		
		void Run();

		static bool Terminate(Application* application);

	private:

		bool m_Open = true;
		bool m_Restart = false;


	};



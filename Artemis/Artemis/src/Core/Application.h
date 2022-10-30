#pragma once


	class Application {

	public:

		static Application* Create();
		
		void Run();

		static void Terminate(Application* application);

	private:

		bool m_Open = true;


	};



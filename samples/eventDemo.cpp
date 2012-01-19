#include <iostream>
#include <Core/EventDispatcher.h>
#include <Core/Callback.h>
#include <Events/Event.h>

using namespace std;

class MyApp: public Core::EventDispatcher{
	public:
		MyApp(){
						
		}
		
		void init(){
			//Define our events
			myCallBack.SetCallback(this, &MyApp::onClick);
			addEventListener("Custom", &myCallBack);
		}			
			

		void onClick(Events::Event e){
			cout << "Event fired\n";
			cout << "Event type: " << e.type << "\n";
		}
		
		void run(){
			//Create event
			Events::Event e;
			e.type="Custom";
			dispatchEvent(e);

			Events::Event e1;
			e1.type="Custom";
			e1.target=this;
			dispatchEvent(e1);			
			
			Events::Event e2;
			e2.type="Custom";
			e2.target=new EventDispatcher();
			dispatchEvent(e2);			
			
		}

	private:
		Core::TCallback<MyApp> myCallBack;	
};

int main ()
{
	cout << "Hello World! ";
	cout << "I'm a C++ program\n";

	MyApp app;
	app.init();
	app.run();
	
	return 0;
}

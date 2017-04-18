#include <nan.h>
#include "prtscn_osx.h"
#include <stdlib.h>

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();


	// Check number of arguments passed
	if (args.Length() < 5) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
		return;
	}

	//Check the argument types
	if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber() || !args[3]->IsNumber()) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
		return;
	}

	int x = args[0]->NumberValue();
	int y = args[1]->NumberValue();
	int width =  args[2]->NumberValue();
	int height = args[3]->NumberValue();

	getScreen(x, y, width, height, *String::Utf8Value(args[4]));

	//Performe the operation
	Local<Function> cb = Local<Function>::Cast(args[5]);
	Local<Value> argv[1] = {Null(isolate)};
	cb->Call(Null(isolate), 1, argv);
}

void Init(Local<Object> exports, Local<Object> module) {
	NODE_SET_METHOD(module, "exports", Method);
}

NODE_MODULE(screenshot, Init)

#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <stdint.h>
#include <nan.h>

extern "C" {
    #include "phi.h"
}

using namespace node;
using namespace v8;

NAN_METHOD(phi) {
    Nan::HandleScope scope;    
    if (info.Length() < 1)
        return Nan::ThrowError("You must provide one argument.");

    Local<Object> target = info[0]->ToObject();

    if(!Buffer::HasInstance(target))
        return Nan::ThrowError("Argument should be a buffer object.");

    char * input = Buffer::Data(target);
    char output[32];

    phi_hash(input, output);
    info.GetReturnValue().Set(Nan::NewBuffer(output, 32).ToLocalChecked());
}


void init(Handle<Object> exports) {
    exports->Set(
        Nan::New<String>("phi").ToLocalChecked(), 
        Nan::GetFunction(Nan::New<v8::FunctionTemplate>(phi)).ToLocalChecked()
    );
}

NODE_MODULE(phi, init)

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

void phi (const Nan::FunctionCallbackInfo<v8::Value>& info) {
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
    exports->Set(Nan::New<String>("phi"), Nan::New<FunctionTemplate>(phi)->GetFunction().ToLocalChecked());
}

NODE_MODULE(phi, init)

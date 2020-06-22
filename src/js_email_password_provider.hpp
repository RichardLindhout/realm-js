////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "sync/app.hpp"

#include "js_class.hpp"
#include "js_sync_util.hpp"

namespace realm {
namespace js {

template<typename T>
class EmailPasswordProviderClientClass : public ClassDefinition<T, app::App::UsernamePasswordProviderClient> {
    using GlobalContextType = typename T::GlobalContext;
    using ContextType = typename T::Context;
    using FunctionType = typename T::Function;
    using ObjectType = typename T::Object;
    using ValueType = typename T::Value;
    using String = js::String<T>;
    using Object = js::Object<T>;
    using Value = js::Value<T>;
    using Function = js::Function<T>;
    using ReturnValue = js::ReturnValue<T>;
    using Arguments = js::Arguments<T>;

public:
    std::string const name = "EmailPasswordProviderClient";

    static FunctionType create_constructor(ContextType);
    static ObjectType create_instance(ContextType, SharedApp);

    PropertyMap<T> const properties = {
    };

    static void register_user(ContextType, ObjectType, Arguments&, ReturnValue&);
    static void confirm_user(ContextType, ObjectType, Arguments&, ReturnValue&);
    static void resend_confirmation_email(ContextType, ObjectType, Arguments&, ReturnValue&);
    static void send_reset_password_email(ContextType, ObjectType, Arguments&, ReturnValue&);
    static void reset_password(ContextType, ObjectType, Arguments&, ReturnValue&);

    MethodMap<T> const methods = {
        {"_registerUser", wrap<register_user>},
        {"_confirmUser", wrap<confirm_user>},
        {"_resendConfirmationEmail", wrap<resend_confirmation_email>},
        {"_sendResetPasswordEmail", wrap<send_reset_password_email>},
        {"_resetPassword", wrap<reset_password>},

    };
};

template<typename T>
inline typename T::Function EmailPasswordProviderClientClass<T>::create_constructor(ContextType ctx) {
    FunctionType constructor = ObjectWrap<T, EmailPasswordProviderClientClass<T>>::create_constructor(ctx);
    return constructor;
}

template<typename T>
typename T::Object EmailPasswordProviderClientClass<T>::create_instance(ContextType ctx, SharedApp app) {
    return create_object<T, EmailPasswordProviderClientClass<T>>(ctx, new app::App::UsernamePasswordProviderClient(app->provider_client<realm::app::App::UsernamePasswordProviderClient>()));
}

template<typename T>
void EmailPasswordProviderClientClass<T>::register_user(ContextType ctx, ObjectType this_object, Arguments& args, ReturnValue& return_value) {
    args.validate_count(3);

    auto& client = *get_internal<T, EmailPasswordProviderClientClass<T>>(ctx, this_object);

    auto email = Value::validated_to_string(ctx, args[0], "email");
    auto password = Value::validated_to_string(ctx, args[1], "password");
    auto callback = Value::validated_to_function(ctx, args[2], "callback");

    client.register_email(email, password, make_callback_handler<T>(ctx, this_object, callback));
}

template<typename T>
void EmailPasswordProviderClientClass<T>::confirm_user(ContextType ctx, ObjectType this_object, Arguments& args, ReturnValue& return_value) {
    args.validate_count(3);

    auto& client = *get_internal<T, EmailPasswordProviderClientClass<T>>(ctx, this_object);

    auto token = Value::validated_to_string(ctx, args[0], "token");
    auto token_id = Value::validated_to_string(ctx, args[1], "token_id");
    auto callback = Value::validated_to_function(ctx, args[2], "callback");

    client.confirm_user(token, token_id, make_callback_handler<T>(ctx, this_object, callback));
}

template<typename T>
void EmailPasswordProviderClientClass<T>::resend_confirmation_email(ContextType ctx, ObjectType this_object, Arguments& args, ReturnValue& return_value) {
    args.validate_count(2);

    auto& client = *get_internal<T, EmailPasswordProviderClientClass<T>>(ctx, this_object);

    auto email = Value::validated_to_string(ctx, args[0], "email");
    auto callback = Value::validated_to_function(ctx, args[2], "callback");

    client.resend_confirmation_email(email, make_callback_handler<T>(ctx, this_object, callback));
}

template<typename T>
void EmailPasswordProviderClientClass<T>::send_reset_password_email(ContextType ctx, ObjectType this_object, Arguments& args, ReturnValue& return_value) {
    args.validate_count(2);

    auto& client = *get_internal<T, EmailPasswordProviderClientClass<T>>(ctx, this_object);

    auto email = Value::validated_to_string(ctx, args[0], "email");
    auto callback = Value::validated_to_function(ctx, args[2], "callback");

    client.send_reset_password_email(email, make_callback_handler<T>(ctx, this_object, callback));
}

template<typename T>
void EmailPasswordProviderClientClass<T>::reset_password(ContextType ctx, ObjectType this_object, Arguments& args, ReturnValue& return_value) {
    args.validate_count(4);

    auto& client = *get_internal<T, EmailPasswordProviderClientClass<T>>(ctx, this_object);

    auto password = Value::validated_to_string(ctx, args[0], "password");
    auto token = Value::validated_to_string(ctx, args[1], "token");
    auto token_id = Value::validated_to_string(ctx, args[2], "token_id");
    auto callback = Value::validated_to_function(ctx, args[3], "callback");

    client.reset_password(password, token, token_id, make_callback_handler<T>(ctx, this_object, callback));
}

}
}

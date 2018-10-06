
#include <webkit2/webkit-web-extension.h>
#include <JavaScriptCore/JavaScript.h>

JSClassRef WebAppInterface();



static char *readFile(char *filename) {
    char *buffer = 0;
    long length;

    FILE *f = fopen(filename, "r");

    if(f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
    
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);

        if(buffer) {
            fread(buffer, 1, length, f);
        }
    
        fclose(f);
        buffer[length] = '\0';
    }

    return buffer;
}

static JSCValue * WebAppInterface_openCollection(
    WebKitWebExtension *extension
) {
    g_assert(WEBKIT_IS_WEB_EXTENSION(extension));

    // todo: use gtk_file_picker ; cannot use gtk here
    // try to use DBUS connection between app/extension if possible ??

GList *gtk_parents = gtk_window_list_toplevels();
GList *l;
int i =5;

for (l = gtk_parents; l != NULL; l = l->next)
{
i++;
  }

  char str[80];

sprintf(str, " Echo : %i", i);

puts(str);
g_message(str);








    //  g_assert(WEBKIT_IS_WEB_PAGE(webPage));



    // JSCContext *context = jsc_context_get_current();

    // char *content = readFile("/home/fox/Bureau/vscode");

    // return jsc_value_new_string(context, content);
}






static void window_object_cleared_callback(
    WebKitScriptWorld *world,
    WebKitWebPage *page,
    WebKitFrame *frame,
    WebKitWebExtension *extension //gpointer user_data
) {
    g_message("extension:window_object_cleared_callback");

    g_assert(WEBKIT_IS_WEB_EXTENSION(extension));

    // extend javascriptCore APi

    JSCContext *jsc_context = webkit_frame_get_js_context_for_script_world(frame, world);
    JSCValue *jsc_globalObject = jsc_context_get_global_object(jsc_context);

    JSCClass *js_class = jsc_context_register_class(jsc_context, "WebkitgtkInterface", NULL, NULL, NULL);

    jsc_class_add_method(
        js_class,
        "openCollection",
        G_CALLBACK(WebAppInterface_openCollection), NULL, NULL,
        JSC_TYPE_VALUE, //G_TYPE_STRING // return type
        0, G_TYPE_NONE // args number and types
    );

    // jsc_class_add_method(
    //     js_class,
    //     "getPoster",
    //     G_CALLBACK(WebAppInterface_openCollection), NULL, NULL,
    //     G_TYPE_STRING,
    //     1, G_TYPE_STRING
    // );


    JSCValue *js_interface = jsc_value_new_object(jsc_context, extension, js_class);

    jsc_value_object_set_property (jsc_globalObject, "WebkitgtkInterface", js_interface);
    g_object_unref (js_interface);






//https://webkitgtk.org/reference/jsc-glib/stable/JSCContext.html#jsc-context-register-class

    // JSGlobalContextRef context = webkit_frame_get_javascript_context_for_script_world(frame, world);

    // JSObjectRef globalObject = JSContextGetGlobalObject(context);

	// JSObjectRef webAppInterfaceObject = JSObjectMake(context, WebAppInterface(), NULL);

	// JSObjectSetProperty(
    //     context, globalObject,
    //     JSStringCreateWithUTF8CString("WebkitgtkInterface"),
    //     webAppInterfaceObject,
    //     kJSPropertyAttributeNone,
    //     NULL
    // );
    //jsc_value_to_string
}

static void web_page_created_callback (
    WebKitWebExtension *extension,
    WebKitWebPage *web_page,
    gpointer user_data
) {
    g_message("extension:web_page_created_callback");

    g_assert(WEBKIT_IS_WEB_EXTENSION(extension));


}


G_MODULE_EXPORT void webkit_web_extension_initialize_with_user_data(
    WebKitWebExtension *extension,
    GVariant *user_data
) {

     g_assert(WEBKIT_IS_WEB_EXTENSION(extension));

    WebKitScriptWorld *webkit_world = webkit_script_world_get_default();




// if(parent_window == NULL){
//     g_message("NULL");
// }




// GtkWidget *dialog;
// GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
// gint res;

// dialog = gtk_file_chooser_dialog_new ("Open File",
//                                       parent_window,
//                                       action,
//                                       "_Cancel",
//                                       GTK_RESPONSE_CANCEL,
//                                       "_Open",
//                                       GTK_RESPONSE_ACCEPT,
//                                       NULL);

// res = gtk_dialog_run (GTK_DIALOG (dialog));







    g_signal_connect(extension, "page-created", G_CALLBACK(web_page_created_callback), NULL);

    g_signal_connect(webkit_world, "window-object-cleared", G_CALLBACK(window_object_cleared_callback), extension);

// G_TYPE_OBJECT, //G_TYPE_FROM_CLASS (extension),
    // guint extension_ready_signal = g_signal_new(
    //     "extension:ready",
    //     G_TYPE_FROM_CLASS(NULL),
    //     G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS, //signal_flags
    //     0, //class_offset
    //     NULL, //accumulator
    //     NULL, //accu_data
    //     NULL, //c_marshaller
    //     G_TYPE_NONE, //return_type G_TYPE_STRING, G_TYPE_VALUE
    //     0, //n_params
    //     NULL // params
    // );

    // g_signal_emit(extension, extension_ready_signal, 0);

    // g_signal_emit_by_name(extension, "extensionloaded");
}










/*

JSObjectRef WebAppInterface_callAsConstructor(
    JSContextRef context,
    JSObjectRef constructor,
    size_t argumentCount,
    const JSValueRef arguments[],
    JSValueRef* exception
) {

}

void WebAppInterface_finalize(JSObjectRef object) {

}

JSValueRef WebAppInterface_openCollection(
    JSContextRef context,
    JSObjectRef function,
    JSObjectRef object,
    size_t argumentCount,
    const JSValueRef arguments[],
    JSValueRef* exception
) {
    JSStringRef response = JSStringCreateWithUTF8CString("{\"ok\":123}");

    return JSValueMakeString(context, response);
}

JSClassRef WebAppInterface () {

    JSClassDefinition classDefinition = kJSClassDefinitionEmpty;

    static JSStaticFunction staticFunctions[] = {
        { "openCollection", WebAppInterface_openCollection, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete },
        // { "saveCollection", WebAppInterface_saveCollection, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete },
        // { "getPoster", WebAppInterface_getPoster, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete },
        // { "savePoster", WebAppInterface_savePoster, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete },
        { 0, 0, 0 }
    };

    classDefinition.className = "WebkitgtkInterface";
    classDefinition.attributes = kJSClassAttributeNone;
    classDefinition.staticFunctions = staticFunctions;
    // classDefinition.staticValues = staticValues;
    classDefinition.finalize = WebAppInterface_finalize;
    // classDefinition.callAsConstructor = WebAppInterface_callAsConstructor;

    JSClassRef bridge_class = JSClassCreate(&classDefinition);

    return bridge_class;
}

*/
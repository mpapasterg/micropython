#include "py/obj.h"
#include "py/runtime.h"

// A MicroPython C module is a module that is compiled with MicroPython and made available at runtime from flash memory instead of RAM. It is similar to the Python C extension modules but with a different Python/C API.

// Define a function that is implemented in C but called from MicroPython
// It needs to accept MicroPython objects of type mp_obj_t and return a MicroPython object. It also needs to be a static function.
static mp_obj_t add_int(mp_obj_t a_obj, mp_obj_t b_obj)
{
  int a = mp_obj_get_int(a_obj);
  int b = mp_obj_get_int(b_obj);
  return mp_obj_new_int(a + b);
}

// For the function to be callable by MicroPython a function MicroPython object needs to be registered in the module. It is defined as a constant function object with a static declaration.
// There are variants of the definition macro for 0-4 arguments passed (the number at the end of the macro name). IF more arguments are required MP_DEFINE_CONST_OBJ_VAR(obj_name, min_args, fun_name) can be used to set the minimum amount of arguments expected. The number of arguments can even be restricted using MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(obj_name, min_args, max_args, fun_name).
static MP_DEFINE_CONST_FUN_OBJ_2(add_int_obj, add_int);

// After defining the function object it needs to be registered at the module globals. The module globals are a table of keys (q-strings for names) of globals available at the module and their corresponding values.
// The module globals are first defined as a key-value paired table in C and then declared as a constant dictionary object in the module.
// Q-strings are constant strings in MicroPython that are compiled in flash memory and accessed through a global q-string repository.
// A q-string can be defined using the MP_ROM_QSTR macro with a  MP_QSTR_<str> q-string in it. This macro will be recognized and compiled into a valid q-string at compile-time. Other macros for defining compile time constants are MP_ROM_PTR for constant pointers and MP_ROM_INT for constant integers.
// A string constant that can contain more complex characters can be defined as a string constant object. A pointer to that object can be then acquired for use in the globals table
static const MP_DEFINE_STR_OBJ(version_str_obj, "0.0.1");
// A tuple object (which is by definition immutable) can be defined by defining a structure of type mp_rom_obj_tuple_t. The tuple should subtype mp_type_tuple and it's number of members and the members should follow.
const mp_rom_obj_tuple_t version_tuple_obj = {
    .base = {&mp_type_tuple},
    .len = 2,
    .items = {
        MP_ROM_INT(1),
        MP_ROM_PTR(&version_str_obj),
    },
};
static const mp_rom_map_elem_t exmod_globals_tb[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_exmod)},
    {MP_ROM_QSTR(MP_QSTR_add_int), MP_ROM_PTR(&add_int_obj)},
    {MP_ROM_QSTR(MP_QSTR___version__), MP_ROM_PTR(&version_str_obj)},
    {MP_ROM_QSTR(MP_QSTR_version), MP_ROM_PTR(&version_tuple_obj)},
};
static MP_DEFINE_CONST_DICT(exmod_module_globals, exmod_globals_tb);

// A table that serves as a header for the module and needs definition in order for the module to be registered in MicroPython is a constant mp_obj_module_t module object. This contains everything the module should contain (like the globals defined above in the globals dictionary) and should subtype the module type.
const mp_obj_module_t exmod_module_obj = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&exmod_module_globals,
};

// The last thing needed to use the module is to register it in MicroPython. The registration includes the name of the module as referenced from MicroPython,
MP_REGISTER_MODULE(MP_QSTR_exmod, exmod_module_obj);
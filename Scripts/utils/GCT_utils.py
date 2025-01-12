import ctypes

def Call(dll_name, func_name, return_type, *args):
    import GCT
    try:
        # Get the loaded library
        dll = ctypes.windll.LoadLibrary(dll_name) if hasattr(ctypes, 'windll') else ctypes.cdll.LoadLibrary(dll_name)
        
        # Get the function
        func = getattr(dll, func_name)
        
        # Set the return value type
        func.restype = return_type
        
        # Explicitly specify the types of arguments
        arg_types = []
        c_args = []
        for arg in args:
            if isinstance(arg, int):
                arg_types.append(ctypes.c_int)
                c_args.append(ctypes.c_int(arg))
            elif isinstance(arg, float):
                arg_types.append(ctypes.c_float)
                c_args.append(ctypes.c_float(arg))
            elif isinstance(arg, str):
                arg_types.append(ctypes.c_char_p)
                c_args.append(ctypes.c_char_p(arg.encode('utf-8')))
            elif isinstance(arg, ctypes.Array):
                arg_types.append(type(arg))
                c_args.append(arg)
            else:
                raise TypeError("Unsupported argument type")

        func.argtypes = arg_types
        
        # Call the function with the given arguments
        result = func(*c_args)
        
        return result
    except Exception as e:
        GCT.DisplayError(False, e)
        return 
    
def array_to_list(array, size, element_type):
    if isinstance(array, ctypes.POINTER(element_type)):
        return [array[i] for i in range(size)]
    return array

def list_to_array(lst, element_type):
    array_type = element_type * len(lst)
    return array_type(*lst)
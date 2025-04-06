#pragma once

#include "input.hpp"

namespace dino::input {    
    size_t get_num_inputs();
    const std::string& get_input_name(GameInput input);
    const std::string& get_input_enum_name(GameInput input);
    GameInput get_input_from_enum_name(const std::string_view name);
    InputField& get_input_binding(GameInput input, size_t binding_index, InputDevice device);
    void set_input_binding(GameInput input, size_t binding_index, InputDevice device, InputField value);

    bool get_n64_input(int controller_num, uint16_t* buttons_out, float* x_out, float* y_out);
}

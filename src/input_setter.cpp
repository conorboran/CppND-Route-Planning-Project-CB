/* 
 *  This function will ensure that the inputs to the search algorithm are within the available coordinates from 0,0 to 100,100
 */

#include "input_setter.h"

std::vector<float> SetInputs()
{
    std::vector<std::string> input_names {"start_x", "start_y", "end_x", "end_y"};
    std::vector<float> inputs;

    for(int i = 0; i < input_names.size(); i++)
    {
        float input = 0.0f;
        std::cout << "Please enter input for " << input_names[i] << "\n";
        std::cin >> input;

        inputs.push_back(input);
    }

    return inputs;
}

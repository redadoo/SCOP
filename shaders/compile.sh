#!/bin/bash

# dir=`dirname $0`
# glslc shader.vert -o $dir/vert.spv
# glslc shader.frag -o $dir/frag.spv


/home/edoardo/vulkan/1.4.313.0/x86_64/bin/glslc shaders/shader.vert -o shaders/vert.spv
/home/edoardo/vulkan/1.4.313.0/x86_64/bin/glslc shaders/shader.frag -o shaders/frag.spv
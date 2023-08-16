forfiles /P shaders /S /M *.vert /C "cmd /c glslc @PATH -o @PATH.spv"
forfiles /P shaders /S /M *.frag /C "cmd /c glslc @PATH -o @PATH.spv"
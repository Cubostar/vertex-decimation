  // ==================================================================
  #version 330 core
  
  // Note: That the 'in' means this is coming from a previous stage of
  //       our pipeline.
  in vec3 theColor;
  
  // The fragment shader should have exactly one output.
  // That output is the final color in which we rasterize this 
  // fragment. We can name it anything we want, but it should
  // be outputting a vec4.
  out vec4 color;

  void main()
  {
   // color is a vec4 representing color. Because we are in a fragment
   // shader, we are expecting in our pipeline a color output.
   // That is essentially the job of the fragment shader--
   // to output one final color.
    color = vec4(theColor, 1.0);
  }
  // ==================================================================

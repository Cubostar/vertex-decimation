// ==================================================================
#version 330 core

layout(location=0)in vec3 position; // We explicitly state which is the vertex information 
				    // i.e., The first 3 floats are positional data, 
				    // we are putting in our position vector
layout(location=1)in vec3 vertexColor; // Our second attribute is the color attributes of each
				       // vertex.
				       
// Note: That both of these 'layout' attributes are marked 'in'. 
//       That means that these are coming 'in' from somewhere.
//       Since this was our first stage of the pipeline, they must
//       be coming in from the CPU--so on our CPU when we 'create a buffer'
//       and setup the data, this is where that data is coming in from.

// Do not forget this!
out vec3 theColor;

uniform mat4 modelTransformMatrix;
uniform mat4 projectionMatrix;

void main()
{
  // gl_Position is a special glsl variable that tells us what
  // postiion to put things in.
  // It takes in exactly 4 things.
  // Note that 'w' (the 4th dimension) should be 1.
  vec4 oldPosition = vec4(position.x, position.y, position.z, 1.0f);

  gl_Position = projectionMatrix * modelTransformMatrix * oldPosition;

  // Store the vertex color that we take in as what we will output
  // to the next stage in the graphics pipeline.
  vec3 temp = normalize(position);
  theColor = vec3(abs(temp.x), abs(temp.y), abs(temp.z));

}
// ==================================================================

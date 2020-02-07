# Assignment One Report

I, &lt;insert name&gt;, certify that this work is my own, submitted for CSCI 3090U in compliance with the UOIT Academic Integrity Policy

1. [60 marks] Reading and Displaying a 3D Model
* coordinates in this model are quite small, so i scaled the vertices by 2000 (2e3)

* there are a large number of vertices in this model, so i can’t use GLushort for the index type, i need to use GLuint. i did that by finding the keyword 'short' and changed it to 'int'

* initially i got a bad chungus

<img src="https://cdn.discordapp.com/attachments/662179346479317022/673370403883974666/unknown.png" width="300">

* but in the end, i got this beautiful chungus

<img src="https://cdn.discordapp.com/attachments/662179346479317022/673675838025105498/unknown.png" width="300">

* the normals are already computed in the line `normals[i] = shapes[0].mesh.normals[i]`, and it's too much work to use the algorithm presented in class to do this, indexing into vertices and and all

* i rotated the bunny about the vertical axis to show the complete model. i did that by adding `angle += .01` in the `display` function, updating the angle in every GLFW main loop

2. [40 marks] Curves
* i plotted the control points, and didn't feel like doing the rest

<img src="https://cdn.discordapp.com/attachments/662179346479317022/675178218822828042/unknown.png" width="300">

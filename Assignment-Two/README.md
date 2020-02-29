# Assignment Two Report

I, `<insert name>`, certify that this work is my own, submitted for CSCI 3090U in compliance with the UOIT Academic Integrity Policy

Almost all the coding is in the shaders, so i only included the shaders as the source code, which can be compiled in Windows.
i did scale the vertices by 400 by adding
`vertices[i] *= 4e2` after line 87, which was my only change to the C code
<!--
so whats the differences between Phong and Gouraud shading? 

and what are the different ways of computing the specular reflection component?

accodring to https://www.haroldserrano.com/blog/what-is-the-difference-between-gouraud-and-phong-shading
> In Gouraud Shading, the color for the fragment is computed in the Vertex Shader. Whereas, in Phong Shading, the color for the fragment is computed in the Fragment Shader

according to the `Rendering - OpenGL Lighting` lecture,

> Gouraud Shading
> - We can move the light model evaluation to the vertex shader, this will give us Gouraud shading
> - This will give us a colour at each vertex which will be interpolated across the polygon
> - Our fragment shader will now be trivial, just one line of code to copy the colour value
-->

- for the Phong shading, i just used the `example6a` shaders as is

- for the Gouraud shading, i moved the light model evaluation (in the Phong fragment shader)
to the vertex shader and named it `example6aG`

- `example6d.fs` and `example6c.vs` are the Phong shading with Blinn-Phong reflection model.
so i just used them as they are too

now for the results:

|Phong `(example6a)`| Gouraud `(example6aG)` | Blinn-Phong `(example6d.fs)` and `(example6c.vs)`  |
| -------------     | ------------- | ------------- |
|   ![][D1d]      |   ![][D2d]  |   ![][D3d]  |
|   ![][B1d]      |   ![][B2d]  |   ![][B3d]  |

[D1d]: https://cdn.discordapp.com/attachments/589248288474136576/683168121460490309/unknown.png
[D2d]: https://cdn.discordapp.com/attachments/589248288474136576/683168366810365954/unknown.png
[D3d]: https://cdn.discordapp.com/attachments/589248288474136576/683168538164330528/unknown.png

[B1d]: https://cdn.discordapp.com/attachments/589248288474136576/683168864711868421/unknown.png
[B2d]: https://cdn.discordapp.com/attachments/589248288474136576/683168923075608595/unknown.png
[B3d]: https://cdn.discordapp.com/attachments/589248288474136576/683168976838459398/unknown.png

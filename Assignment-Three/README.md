# Assignment Three Report

I, `<insert name>`, certify that this work is my own, submitted for CSCI 3090U in compliance with the UOIT Academic Integrity Policy

i should be able to do everything in the shader code, so i only included the shaders. the rest of the source code is identical to example 10

for the Reflection and Refraction section,
first i modified `example10a.fs` by changing `tc = reflect(position - Eye, normal)` to `tc = refract(position - Eye, normal,1.5)`, choosing 1.5 as the extra parameter, the index of refraction

after that, i approximated the fraction of reflected light by the Schlick approximation in the line `r = R0 + (1.0 - R0) * pow(1.0 - cosTheta, 5.0)`, with `cosTheta = dot(E, N)` and `R0 = 3/2`

i combined the reflected and refracted light in the line `FragColor = r * texture(tex, reflectTex) + (1 - r) * texture(tex, refractTex)`

i couldnt get the outer ring to show up on my mac. my `r` value was negative. i guess it has to do with how mac deals with adding texture values and things of that nature.

here are some sample images produced by my program

|just refraction| Schlick approximation |
| -------------     | ------------- 
|   ![][D1]      |   ![][D2]  |

[D1]: https://cdn.discordapp.com/attachments/589248288474136576/691850425389023252/unknown.png
[D2]: https://cdn.discordapp.com/attachments/589248288474136576/691850149001035776/unknown.png
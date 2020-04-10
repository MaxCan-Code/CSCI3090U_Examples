# Assignment Four Report

I, `<insert name>`, certify that this work is my own, submitted for CSCI 3090U in compliance with the UOIT Academic Integrity Policy

## Visualization One
i cant be bothered to read in the particle traces of the wind field, so i just made up my own path and produced the line strips that way

## Visualization Two
The technique i used to to compute the tube vertices is:
1. Compute the vector from the current point on the path to the next point on the path.
    ```c++
    glm::vec3 pair[] = {
            glm::vec3(-.5, .5, -.5), //0
            glm::vec3(-.5, -.5, .5), //1
    };
    glm::vec3 diff = pair[1] - pair[0];
   ```
2. Find the two largest components of this vector and swap them. Change the sign of one of the components.

    note: this act of swapping and negating is akin to finding a plane normal by taking the negative reciprocal to the `diff` vector on the plane
    ```c++
    float minh = glm::min(glm::min(x, y), z);
    if (x <= minh) { swap = glm::vec3(x, -y, z); }
    else if (y <= minh) { swap = glm::vec3(-z, y, x); }
    else swap = glm::vec3(-y, x, z);
    ```
3. Take the cross product of the original vector and the vector from step 2 to produce the first output.
    ```c++
    kris = glm::cross(diff, swap);
    ```
4. Take the cross product of the original vector and the vector from step 3 to produce the second output.
    ```c++
    kross = glm::cross(kris, swap);
    ```
then i added and subtracted (all 4 combinations) these two vectors   from the point on the path to get the vertices for the tube

i  cant be bothered to figure out the indexes i need to connect up the vertices from the previous point and the current point to construct the 8 triangles that make up the current tube segment, so my output is scuffed

here are some kites i made with the tube visualization technique

Visualization Two| Visualization Two 
 -------------     | ------------- 
   ![][D1]      |   ![][D2]  

[D1]: https://cdn.discordapp.com/attachments/662179346479317022/697184220237529213/Image_2020-04-07_at_4.38_PM.JPG
[D2]: https://cdn.discordapp.com/attachments/662179346479317022/697186358787047434/Image_2020-04-07_at_4.49_PM.JPG
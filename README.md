# collisionsplusplus
### References
This video has saved me a lot of time. Use [this link](https://www.youtube.com/watch?v=AUFZnA3lW_Q) to setup freeglut/opengl.

Equations will be drafted and included in a pdf soon.

Poisson-disc generator used by: [this github repo](https://github.com/corporateshark/poisson-disk-generator)


### Usage
First run 
```
make
```
to compile the simulation. This will create the exectuable name 'sim.exe'.    

Now you have two options. You can either attempt to simulate in real time by doing
```
./sim.exe
```
Or you can first render the simulation, then play it out once the rendering is finished using:

```
./sim.exe <NUM_SECONDS> 
```
where `NUM_SECONDS` is the number of seconds that you would like the simulation to loop through.    

# evosim

Evosim is a small evolution simulator.

Evosim uses the SDL2 library for graphics. The program can be compiled by simply running `make` in the evosim directory. 

## Using evosim

The simulation starts out with a few organisms that can have children with eachother, grow and die. Each organism has genes which it can pass on to its offspring. The genes affect the size, color and speed the organism, the organism may also carry a gene without it being "active".

By left-clicking on an organism the organism is killed and its genes will not spread further. This is how the user can effect the gene pool of the population. The user can also halve the population by pressing 'H'. 
 
### Two population mode

You may also split the simulation into two populations by pressing 2. By right-clicking on an organism it migrates from one area/population to another. The two populations are totally separated from eachother.


### Keybindings

| Key 	| Action |
|-------|-------------|
| H	| Halve the population							|
| +	| Speed the simulation up 						|
| -	| Slow the simulation down 						|
| Enter	| Return the simulation to it's normal speed				|
| s	| Toggle "single-step" mode						|
| Space | Manually create new generation of organisms (when in single-step mode)|
| 1	| Enter 1 population mode 						|
| 2	| Enter 2 populations mode						|


## What is evosim for?

With this very simple program you can demonstrate and play around with microevolution by, for example, removing all organisms of a certain color and seeing what happends (directional selection), etc.

This program has the potential to demonstrate many basic concepts of evolution, for example: by splitting the population in two you can demonstrate the founder effect, by halving the population you can demonstrate the bottleneck effect or by just letting the simulation be you can demonstrate genetic drift.

## License 

This project is licensed under the terms of the ISC license, see the [LICENSE](LICENSE) file for further information.

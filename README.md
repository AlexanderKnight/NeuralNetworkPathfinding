# Neural Network Pathfinding
## HPC 2019 - University of New Hampshire
### Final Project
#### Alexander Knight

![Time=0, 50 Seekers, 20x20 domain with randomChance = 25](https://user-images.githubusercontent.com/15788315/58054722-764acd00-7b29-11e9-8bae-985088378e4b.png)

[Time=143, 50 Seekers, 20x20 domain with randomChance = 25](https://user-images.githubusercontent.com/15788315/58054747-8ebae780-7b29-11e9-89fb-0d1faf2fce78.png)

[Time=199, 50 Seekers, 20x20 domain with randomChance = 25](https://user-images.githubusercontent.com/15788315/58054760-9a0e1300-7b29-11e9-8c40-42491e4955a2.png)

### Installation Instructions:

1) Clone repo from github
2) Move into directory
3) Run the following commands (assuming Linux/Unix):

```bash
mkdir build
mkdir build/PositionalData
```

4) Adjust the operating parameters for the domain in create_domain.cpp.
- Set width = integer
- Set height = integer
- Set randChance = integer between 0 and 100

Note, that the randChance determines the number of randomly placed obstacles, so it must be low enough for the seekers to have a path through. 25-30 is a good starting point.

5) Adjust the operating parameters for the simulation in main.cpp
- Match domain info for load_domain_filename, gridx, and gridy
- Set number of seekers **Note: This number MUST be divisible by the number of cores**
- Set runtime for each iteration. Somewhere around 2 X (width+height) should be good.
- Set number of iterations. I have not found a good number for this, but it seems that for the 
	current learning I have coded, this number may need to be very high.
	For the time, I set mine ~4-5 X seeker_num, and ~2 X runtime

6) Change directory to build, then run

```bash
cmake ..
make
./create_domain
```

Here the create_domain function will ask you to check that the current map is actually solvable. 

Walls are represented by 1's and open space by 0's. Make sure that there is a path between the upper left and the lower right, then type "Y" (capital y). Else type "N" (capital n) and it will generate a new map.


7) Then, run

```bash
mpirun -n N ./pathfinder
```

where N is the number of cores, and where seekers/N is an integer.

8) To visiualize data, change plot_positions.py to match data:

- Change domain_file to match domain filename
- Match seekers to seeker_num in main.cpp
- Set number of cores that ./pathfinder was run with
- Set domain_x to domain width
- Set domain_y to domain height

and then, from the build directory, run

```bash
python ../plot_positions.py
```

Chances are that the ./pathfinder program made many files, so we can tar them up with

```bash
cd PositionalData
tar -cvf pos_files.tar pos_procseeker* --remove-files
```

## Parallelization Notes

Parallelization starts at line 88 in main.cpp.

Main parallelization occures when each processor operates several seekers, then communicates a message containing each seeker's score, owner core, number on that core, and status to leave, mutate, or reset.

Each message is sent to core 0, and then core 0 sorts them according to their score, and then shifts the status on some to mutate, and on some more to reset, leaving the successful ones alone.

The messages are then sent back to their owner cores and those cores leave/mutate/reset their seekers.

This is done every iteration, so that given enough iterations, the population will improve at the job of getting to the end.

## Current Problems

- Collision checking seems to be failing, either killing the seeker in open space, or not killing them when they impact a wall.
	This may also be that the plotting is incorrect, and does not line up with what the seekers see.

- Score and sorting seems to be buggy, as runs that go long seem to sometimes get reset, despite the fact that they are definitly in the top 20% of score

- Inexperience on my end probably means that the networks themselves are probably buggy, and not being setup properly

- Leaving the top seekers along, mutating the central population, and resetting the bottom is inefficient for solving the maze. Ideally, the top would be copied and mutated to replace the bottom, but sending entire custom objects by MPI was very complicated, requiring serializing the object, and unpacking on the other end.

- Many of the class functions are not used, but in there for the eventual improval.

 
## Further Steps

- I want to learn how to send entire objects over MPI, so that I can copy the best seekers, and then mutate them to replace the worst.

- The network itself is a little buggy, and seems to sometimes give outputs of just 0. for all outputs. This should not happen, so that bug needs to be tracked down. The current fix is to manually set the seeker to move down and left when it doesn't want to move. 

- At the time of this submission, not all of the object classes have been commented, and will be commented on very soon. This is an easy (and necessary) fix.

- Saving good seekers and loading them again is not trivial, considering the amount of data that goes into each network, so I want to find a way to save them in the long run. Saving the object's data directly seems prefered, instead of exporting all the various variables of the network.


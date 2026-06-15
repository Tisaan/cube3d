*This project has been created as part of the 42 curriculum by tseche, pcaplat*

# Cub3D

## Description

Cub3D is one of the graphical projects from the 42 school common core. In this project,  
we had to implement a basic raycaster, similar to Wolfenstein 3D from *id Software*.  
This project is all about using graphical libraries and implementing mathematics in code.  
You have to draw a 3D representation of a 2D grid.

## Instructions

### Compilation

To compile the mandatory part of the project:
```bash
make
```

To recompile the mandatory part from scratch:
```bash
make re
```

To compile the bonus part of this project:
```bash
make bonus
```

To remove object files:
```bash
make clean
```

To remove object files and the executable:
```bash
make fclean
```

### Usage

To run a map:
```bash
./cub3D path_to_map.cub
```

In the bonus part, you can generate maps with procedural generation:
```bash
./cub3D seed
```

You can use your own seed:
```bash
./cub3D seed 012345678901
```

***WARNING***: the seed must be 12 digits long.

## Resources

- [xitog - Raycasting](https://xitog.github.io/dgx/passetemps/tech_raycasting_fr.html)  
- [lodev - Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [Generation README](Generation.md)

## AI usage

No generative AI was used in this project. AI was used to better understand some concepts and to help with bugs we couldn't solve. AI was also used to correct the spelling in this README.

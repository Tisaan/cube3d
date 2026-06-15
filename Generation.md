# Procedural Generation

## Overview
### Component
- **seed**:<br> &emsp;12 digit-long number.
- **height**:<br> &emsp;the height of the grid where the generation take place, correspond to the 5 to 7 digit of the seed divide by 4.
- **width**:<br> &emsp;the width of the grid where the generation take place, correspond to the 8 to 10 digit of the seed divide by 4.
- **ori_x**:<br> &emsp;the x-axis coordonate where the generation start.
- **ori_y**:<br> &emsp;the y-axis coordonate where the generation start.
- **iteration**:<br> &emsp;the number of iteration the algorithm go throught, correspond to the last 2 digit of the seed time 100.
- **door_chance**: <br> &emsp; the chance that a door "spawn" [¹](#door-reference), corresponding to the last number of the seed time 10, e.g (9 -> 90%)
- **wall**: represented as `'1'`
- **floor**: represented as `'0'`
- **door**: represented as `'D'`

### Step
- Seeding:<br> &emsp;if no seed provided, generate a 12 digit long random number, then check that **ori_x** is below **height** and **ori_y** is below **width**, **seed** could be provide with the "-(s/S/seed)" argument
- **Generation**:<br> &emsp;
  The generation algorithm iteratively throught 6 phase:
  - Placement: starting from **ori_x** and **ori_y** place a `'0'` or a `'1'`
  - Linking: place a `'0'` between adjacent `'0'`, e.g (`"0 0"` -> `"000"`)
  - Connecting: calculate the 2 biggest `'0'` region and connect them with the shortest path between them, the path is fill with `'0'`
  - wall: place `'1'` on empty moore-neighboor of a `'0'`, e.g:
	<br>`"⠀⠀  "` &emsp; `"111"`
	<br>`"⠀0⠀"` -> `"101"`
	<br>`"⠀⠀   "` &emsp; `"111"`
  - Doors: try to place a door when a `'1'` has 2 adjacent `'0'` with a **door_chance** probability;
  - Start: we still need to have a starting point to spawn so we'll take to closest[²](#spawn-reference) `'0'` of **ori_x** and **ori_y**

## In-depth implementation
- Generation:
  ```c
  	void	generate_map(map, seed)
	{
		char	*str_seed = binary_representation(seed);
		int			pos[2] = {ori_x, ori_y};//position where we place the char {x, y}
		const int	dir_x[8] = {1, -1, 1, 0, 0, -1, 1, -1};// moore neighboorhood
		const int	dir_y[8] = {-1, 1, -1, 0, 0, 1, -1, 1};
		int			i = 0;// number of iteration
		int			total = 0;// number of time we encounter a already place '0'
		size_t			index = 0;// index to get the character to place

		while (i < iter)
		{
			if (index >= len(str_seed))// reset the counter to avoid segfault
				index = 0;
			if ((pos[0] < height && pos[0] >= 0)
				&& (pos[1] < width && pos[1] >= 0))// if the position is in the grid
			{
				// already place a '0', see reference for further explanation
				if (map[pos[0]][pos[1]] == '0')
				{
					//update the position for the next iteration
					pos[0] = pos[0] + dir_x[(map->iter - i + total) % 8];
					pos[1] = pos[1] + dir_y[(i - map->iter) % 8];
					total++;
					if (total == map->iter)// avoid infinite loop
						break ;
					continue ;
				}
				// place the character either '0' or '1'
				map->map[pos[0]][pos[1]] = str_seed[index++];
			}
			else
			{
				// restart from the original position
				pos[0] = map->ori_x;
				pos[1] = map->ori_y;
			}
			// get the next position in a l_shape like the knight in chess
			// and then one of is moore-neighboor
			l_shape(pos, i);
			pos[0] = pos[0] + dir_x[(map->iter - i + (i % 2 == 0)) % 8];
			pos[1] = pos[1] + dir_y[(i - map->iter + (i % 2 == 1)) % 8];
			i++;
		}
		link_zero(map);// place '0' between adjacent one
		place_struct(map, seed);//place "random" '1' for more wall
		apply_wall(map);// place wall around '0'
		place_door(map);// place the doors
		place_start(map);// place the spawn point
	}
  ```


### door-reference:
 &emsp;- doors are the only non-deterministic "object" of the generation 'cause there are generate with the help of pseudo-randomness.

### spawn-reference:
- we use the chebychev distance to get the closest possible spawn point. MAX(abs(**ori_x** - **x**), abs(**ori_y** - **y**))

### algorithm-reference:
- already-place `'0'`': we only check for `'0'` and not `'1'` 'cause we want `'1'` to be replace to maximize the size of the map
- place_struct: for each cell, if it's an `'0'` and have more than 6 `'0'`'s neighboor replace it with a `'1'`
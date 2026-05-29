# Leaks

## parser

```bash
==29104== Memcheck, a memory error detector
==29104== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==29104== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==29104== Command: ./cub3D test.cub
==29104== 
Invalid map
==29104== 
==29104== HEAP SUMMARY:
==29104==     in use at exit: 27 bytes in 1 blocks
==29104==   total heap usage: 34 allocs, 33 frees, 176,189 bytes allocated
==29104== 
==29104== 27 bytes in 1 blocks are still reachable in loss record 1 of 1
==29104==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==29104==    by 0x4068EF: gnl_calloc (get_next_line_utils.c:55)
==29104==    by 0x406986: ft_strfdup (get_next_line_utils.c:71)
==29104==    by 0x406AD1: gnl_substr (get_next_line_utils.c:99)
==29104==    by 0x4064C4: get_next_line (get_next_line.c:115)
==29104==    by 0x4021AD: parse_map_data (map_data.c:103)
==29104==    by 0x401BC0: parse_map (parser.c:61)
==29104==    by 0x401E21: parse_step (parser.c:89)
==29104==    by 0x401D79: parse (parser.c:118)
==29104==    by 0x4013AC: main (main.c:81)
==29104== 
==29104== LEAK SUMMARY:
==29104==    definitely lost: 0 bytes in 0 blocks
==29104==    indirectly lost: 0 bytes in 0 blocks
==29104==      possibly lost: 0 bytes in 0 blocks
==29104==    still reachable: 27 bytes in 1 blocks
==29104==         suppressed: 0 bytes in 0 blocks
==29104== 
==29104== For lists of detected and suppressed errors, rerun with: -s
==29104== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
This leak append when the map file contain only a grid
The same leak occurs when a path or a texture is missing and when there is only color or texture

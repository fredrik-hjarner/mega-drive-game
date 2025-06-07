This is how I have layed out the VRAM memory map.
Maybe I should think about if I could optimize the positions of the various
tables.

Screen sizes:
    - either 32 or *40* tiles wide.
    - either 30 or *28*  tiles high.

Possible planes sizes are:

| Height in tiles | Width in tiles | Total tiles    |
|-----------------|----------------|----------------|
| 32              | 32 ( px)       | 1024d = 0400h  |
| 64              | 32 ( px)       | 2048d = 0800h  |
| 128             | 32 ( px)       | 4096d = 1000h  |
| 32              | 64 ( px)       |                |
| 64              | 64 (320h px)   | 4096d = 1000h  |
| 128             | 64 ( px)       |                |
|                 |                |                |
|                 |                |                |
|                 |                |                |

VRAM Memory Map

| Address | Description                     | Size    |                        |
|---------|---------------------------------|---------|------------------------|
| $0000   | Window                          | 0 bytes | 2 bytes per tile       |
| $0000   | Tiles                           |         | 32 bytes per tile      |
| $0800   | Horizontal Scroll (full screen) | 4 bytes | 2 bytes per plane      |
|         | Horizontal Scroll (tile)        |         | 2 bytes per tile?      |
|         | Horizontal Scroll (pixel)       | 640h    | 2 bytes per pixel      |
| $2000   | Plane A                         |         | 2 bytes per tile       |
| $6000   | Plane B                         |         | 2 bytes per tile       |
| $8000   | Sprites                         |         |                        |
| $FFFF   | End of VRAM                     |         |                        |
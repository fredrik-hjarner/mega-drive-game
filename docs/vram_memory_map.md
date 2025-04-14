This is how I have layed out the VRAM memory map.
Maybe I should think about if I could optimize the positions of the various
tables.

| Address | Description       | Size    |                       |
|---------|-------------------|---------|-----------------------|
| $0000   | Tiles             |         | 32 bytes per tile     |
| $0400   | Horizontal Scroll | 4 bytes | 2 bytes per dimension |
| $2000   | Plane A           |         | 2 bytes per tile      |
| $4000   | Window            |         | 2 bytes per tile      |
| $6000   | Plane B           |         | 2 bytes per tile      |
| $8000   | Sprites           |         |                       |
| $FFFF   | End of VRAM       |         |                       |
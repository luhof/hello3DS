## Hello3DS

3DS homebrew, iterates until reaching a small game engine.
Currently exports projects as .3dsx format

## what you need

- 3DS (old or new) with a CFW (homebrew launcher installed)
- devkitPro http://3dbrew.org/wiki/Setting_up_Development_Environment

### dependencies

- ctrulib https://github.com/smealum/ctrulib
- sf2dlib https://github.com/xerpi/sf2dlib
- sfillib https://github.com/xerpi/sfillib
- libpng / libjpeg (just use https://github.com/devkitPro/3ds_portlibs)


### current features

- Can display shapes (squares, circles based on sf2d)
- Load and display PNG/JPEG images at different depth levels
- Touchscreen / D-PAD / Buttons interactions to move object, change background...
- superb Bojack / <a href="http://ingenieur-imac.fr">IMAC</a> themed homebrew !<br/>
<img src="http://i.imgur.com/PWSaSne.png"/>

### next

- text
- auto 3D drawing by adding a depth param to objects
- _3D model loading ? --> might wait because needs to get rid of 2D libs and use openGL from scratch_

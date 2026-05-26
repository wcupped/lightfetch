# WARNING
This project is deprecated, it's better version is at [wcupped/sucklessfetch](https://github.com/wcupped/sucklessfetch). I'll try to actively maintain it, thx. [wcupped/rightfetch](https://github.com/wcupped/rightfetch) also prob will be not maintained, but I will not archive it

# Lightfetch - Lightweight alternative to Fastfetch
This utility is specified to create Fastfetch lightweight alternative, the first version has only 115 lines of C++ code

# Some cool stuff
For now, you can specify -j (or --joke) flag to get a random joke on a last line that is being selected from `dumb_jokes` array, all the contributions and other little dumb comedians (like me) are OF COURSE will be appreciated, all the improvements are also welcome.

# Installation
## First of all clone this repository
```sh
git clone --depth 1 https://github.com/wcupped/lightfetch.git
```

## After that you need to run `make` command
```sh
make
```

And you can run executable from `build/` directory, but if you want to install it in your system, run:
```sh
doas make install
```

Good luck using lightfetch!

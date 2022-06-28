
# Test Circle Language

`Circle-lang` is a great language developed by Sean Baxter that extends standard C++ to support more user-friendly grammars, it supports CUDA programming as well. For more, see [here](https://www.circle-lang.org/).

This repo tries to explore the `circle-lang` ability to write high-performance codes.

Preparation:
```bash
# install the latest circle-lang
wget https://www.circle-lang.org/linux/build_170.tgz
tar -xvzf build_170.tgz
# make sure you can find it
export PATH=$PATH:`pwd`
```

Run Example:
```bash
cd examples/1_meta/1_taylor
# run example
circle meta1.cxx
./meta1 0.5
```

# BMP processor

This is the program performs:
- Parsing header of bmp
- Calculating color histogram
- Converting bmp to grayscale
- Encoding-decoding steganography

## Installation
First, copy the repository and run there cmake as follows:
```
git clone https://github.com/AndrewChmutov/BMPprocessor
cd BMPprocessor
cmake -S . -B build
```
It will make configurations for compilation.<br>
Then, go to directory 'build' and compile it:
```
cd build
make
```

---

## How to use

### Parse header and print color histogram

```
./main PATH-TO-BMP
```
If you want to try to decode steganograpy, confirm the request.

### Convert to gray colors

```
./main PATH-TO-TARGET PATH-TO-NEW
```

### Encode steganography

```
./main PATH-TO-TARGET PATH-TO-NEW "text"
```
Text is allowed up to 256 letters.
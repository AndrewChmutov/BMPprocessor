# BMP processor

This is the program performs:
- Parsing header of bmp
- Calculating color histogram
- Converting bmp to grayscale
- Encoding-decoding steganography

---

## How to use

### Parse header and print color histogram

```
./bmp PATH-TO-BMP
```
If you want to try to decode steganograpy, confirm the request.

### Convert to gray colors

```
./bmp PATH-TO-TARGET PATH-TO-NEW
```

### Encode steganography

```
./bmp PATH-TO-TARGET PATH-TO-NEW "text"
```
Text is allowed up to 256 letters.

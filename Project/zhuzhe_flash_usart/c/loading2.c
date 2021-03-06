//ScreenKeys
//
//Produced by TFT ScreenKey Image Editor:
//    8bit RLE compressed Image
//    Width: 128
//    Height: 128
//
//The array structure is as follows:
//		Cmd byte (0x27 for 8-bit RLE compressed image)
//		XOR byte value for the cmd byte (0xD8)
//		Bytes 3/4 are the hex values of the image data size plus 4 (bytes 5/6/7/8) (MSB/LSB)
//		Bytes 5/6 are the X and Y positions of the top-left corner of the image when displayed on the TFT Key
//		Bytes 7/8 are the width and height of the image in pixels
//		The remaining bytes are the actual image data
//
//The size of the array is the size of image data (image width multiplied by height).
//The '+8' is to account for the addition of the TFT command header.
//
const char loading2[1134+8] = { 
    0x27, 0xD8, 0x04, 0x72, 00, 00, 128, 128,
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x07, 0xFF, 0x2A, 0x00, 0x00, 0x00, 
    0x4E, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x05, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x29, 0x00, 0x00, 0x00, 
    0x0C, 0x00, 0x08, 0xFF, 0x05, 0x00, 0x05, 0xFF, 0x05, 0x00, 0x09, 0xFF, 0x00, 0x03, 0x00, 0x00, 
    0x00, 0x35, 0x07, 0xFF, 0x00, 0x03, 0x00, 0x00, 0x00, 0x20, 0x06, 0xFF, 0x04, 0x00, 0x04, 0xFF, 
    0x01, 0x00, 0x04, 0xFF, 0x00, 0x05, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xE4, 0x04, 0x00, 0x00, 0x07, 
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x3F, 0x08, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x3F, 
    0x08, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x3F, 0x0E, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x01, 0xFF, 
    0x01, 0xFF, 0x04, 0x00, 0x00, 0x11, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0x04, 0xFF, 0x00, 0x09, 0x00, 0x00, 
    0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xE4, 0x06, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x07, 0x00, 
    0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x05, 0x00, 0x06, 0xFF, 0x00, 0x06, 
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0x08, 0x00, 
    0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x01, 0xFF, 0x01, 0xFF, 
    0x04, 0x00, 0x00, 0x06, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x05, 0x00, 0x00, 0x06, 0xFF, 0xFF, 
    0x00, 0x00, 0xFF, 0xFF, 0x04, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
    0x04, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x06, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x07, 0x00, 0x00, 0x07, 
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x2F, 0x00, 
    0x00, 0x00, 0x0D, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x08, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x05, 0x00, 
    0x00, 0x11, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 
    0x00, 0xFF, 0xFF, 0x00, 0x04, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x06, 0x00, 0x01, 0xFF, 0x01, 0xFF, 
    0x07, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x05, 0x00, 0x05, 0xFF, 
    0x2B, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x08, 0x00, 0x01, 0xFF, 0x01, 0xFF, 
    0x05, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x05, 0x00, 0x05, 0xFF, 0x00, 0x05, 0x00, 0x00, 0x00, 0xFF, 
    0xFF, 0x00, 0x04, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x06, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x07, 0x00, 
    0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x04, 0x00, 0x00, 0x07, 0xFF, 0xFF, 
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x01, 0xFF, 0x01, 0xFF, 
    0x08, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x05, 0x00, 0x00, 0x06, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 
    0x04, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x04, 0x00, 0x01, 0xFF, 
    0x01, 0xFF, 0x06, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x07, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 
    0x00, 0xFF, 0xFF, 0x07, 0x04, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 
    0x2A, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x09, 0x00, 0x00, 0x0C, 0xFF, 0xFF, 
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x04, 0x00, 0x01, 0xFF, 0x01, 0xFF, 
    0x04, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x06, 0x00, 0x01, 0xFF, 
    0x01, 0xFF, 0x07, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x04, 0x00, 
    0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x0D, 0x00, 
    0x01, 0xFF, 0x01, 0xFF, 0x0A, 0x00, 0x05, 0xFF, 0x05, 0x00, 0x06, 0xFF, 0x06, 0x00, 0x06, 0xFF, 
    0x04, 0x00, 0x04, 0xFF, 0x06, 0x00, 0x07, 0xFF, 0x06, 0x00, 0x07, 0xFF, 0x29, 0x00, 0x00, 0x00, 
    0x0D, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x24, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x4B, 0x00, 0x00, 0x00, 
    0x0D, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x24, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x4B, 0x00, 0x00, 0x00, 
    0x0D, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x24, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x4B, 0x00, 0x00, 0x00, 
    0x0D, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x24, 0x00, 0x01, 0xFF, 0x01, 0xFF, 0x05, 0x00, 0x00, 0x03, 
    0xFF, 0xFF, 0xFF, 0x00, 0x43, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x04, 0xFF, 0x22, 0x00, 0x00, 0x03, 
    0xFF, 0xFF, 0xFF, 0xFF, 0x05, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0x43, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01
};

# delgaaps

Deleting Google and Mi services has become even easier and more convenient. It is enough to specify the folder in which the firmware image is unpacked, the name of the image without extension and the file with regular expressions.

## Usage:
```
     delgaaps <folder> <name_image> <file_list>
```
Where:
`<folder>` - path to the folder where the image was unpacked
`<name_image>` - image name without extension (.img)
`<file_list>` - a file with a list of regular expressions to remove gaaps and more
## Example:
This is a simple example on a Linux system:
```
~$ ./delgaaps "/local/UnpackerSystem" "system" "./gappslist.txt"
```
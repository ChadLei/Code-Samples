'''
DIRECTIONS:

Write a function that accepts a string as input and 
returns the color that it represents as a 32-bit integer where 
the red component is store in the lowest byte, 
the green component is stored in the second-lowest byte, 
and the blue component is store in the third lowest byte.

RESTRICTIONS:

Can not use library functions to convert the hex digits to numbers
Can not use regular expressions

INPUT / OUTPUT EXAMPLES:

"#F00"    -> 255 (red)
"#800080" -> 8388736 (purple)
"#ffa500" -> 42495 (orange)
"oops"    -> Error
'''

def css_string_to_color(colorString):
    hexValue = colorString[1:].upper()
    hexConversion = {'A':10,'B':11,'C':12,'D':13,'E':14,'F':15}
    rgb = {'r':[],'g':[],'b':[]}
    rgbValues = []
    sum = 0
    count = 0
    
    # checks if input is in short format: if it is, change it to long format 
    if len(hexValue) == 3:
        temp = ""
        for i in hexValue:
            temp += i
            temp += i
        hexValue = temp
        
    # checks if input is a valid hex value
    if colorString[0] != '#':
        raise ValueError("Error")

    # retrieves and converts respective RGB values
    for i in range(len(hexValue)):
        if i == 0 or i == 1:
            if hexValue[i] in hexConversion.keys():
                rgb['r'].append(hexConversion[hexValue[i]])
            else:
                rgb['r'].append(int(hexValue[i]))
        elif i == 2 or i == 3:
            if hexValue[i] in hexConversion.keys():
                rgb['g'].append(hexConversion[hexValue[i]])
            else:
                rgb['g'].append(int(hexValue[i]))
        elif i == 4 or i == 5:
            if hexValue[i] in hexConversion.keys():
                rgb['b'].append(hexConversion[hexValue[i]])
            else:
                rgb['b'].append(int(hexValue[i]))

    # switches from RGB to BGR (given that red is stored in lowest byte, etc.)
    rgbValues.append(rgb['b'])
    rgbValues.append(rgb['g'])
    rgbValues.append(rgb['r'])

    # converts each value into 16 byte hex and stores the sum as 32 bit integer
    for color in range(len(rgbValues)-1, -1, -1):
        for value in range(len(rgbValues[color])-1,-1,-1):
            sum += rgbValues[color][value] * (16**count)
            count += 1
        
    colorString = sum
    return (colorString)